
# coding: utf-8

# In[1]:


import os 
import time 

os.environ["OPENBLAS_NUM_THREADS"] = '1'

import numpy as np 
from mpi4py import MPI 
import time

np.random.seed(42)
# generates random data
def get_data(X,y,n):
    x1=[]
    y1=[]
    for i in range(0,4):
        for j in range(0,n):
            noise=np.random.normal(0,0.001,size=(2,1))
            x1.append(X[i].reshape(2,1)+noise)
            y1.append(y[i]+np.random.normal(0,0.001))
    x1=np.array(x1)
    y1=np.array(y1)
    return x1,y1

### constructs a tree using ranks and returns the dictionary
def construct_tree(n,L):
	G = {}
	num_parents = int(1 + 3*(3**(L-1) - 1)/2)
	for i in range(num_parents):
		G[str(i)] = []
		for j in range(n):
			G[str(i)].append(3*i + j + 1)
	return G

B = np.array([[0.5,1.0,0.0],[0.0,1.0,-1.0],[0.5,0.0,1.0]])
A = np.array([[0.0,1.0,2.0],[1.0,0.0,1.0],[2.0,-1.0,0.0]])
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
total_workers = comm.Get_size()-1
L = 2
stragglers = 1

X_orig=np.array([[1,0],[0,1],[1,1],[0,0]])
y_orig=np.array([1,1,1,0])
number_train_samples = 1200
learning_rate = 1e-2
num_epochs = 100
W=np.random.normal(0,1,(2,1))
b=np.random.normal(0,1,(1,1))
beta = 0.02 ### delay for each worker
stragglers = 1
data=get_data(X_orig,y_orig,number_train_samples)
total = 3
time_total = 0
tree = construct_tree(3,L)
fraction = 4.0/15.0 ### fraction assigned to a worker
num_workers = 3
# In[2]:




def layer(w,x,b):
    out = np.matmul(w.T,x)+b
    return out

# derivative of sum of square error function
def mse(y_true,y_pred):
    return (y_true-y_pred)**2


def compalloc(data,W,b,parent_rank):
	partitioned_x = np.split(data[0],3)
	partitioned_y = np.split(data[1],3)
	for i in range(3):
		x_sent = []
		y_sent = []
		for j in range(3):
			if B[i,j] != 0:
				x_sent.append(partitioned_x[j])
				y_sent.append(partitioned_y[j])
		comm.send((x_sent,y_sent,W,b),dest = 3*parent_rank + i + 1)

def compalloc2(data,label,W,b,parent_rank):
	d1_x = np.split(data[0],3)
	d2_x = np.split(data[1],3)
	d1_y = np.split(label[0],3)
	d2_y = np.split(label[1],3)
	for i in range(3):
		d1_sent_x = []
		d2_sent_x = []
		d1_sent_y = []
		d2_sent_y = []
		for j in range(3):
			if B[i,j] != 0:
				d1_sent_x.append(d1_x[j])
				d2_sent_x.append(d2_x[j])
				d1_sent_y.append(d1_y[j])
				d2_sent_y.append(d2_y[j])
		comm.send((d1_sent_x,d2_sent_x,d1_sent_y,d2_sent_y,W,b),dest = 3*parent_rank + i + 1)

#### computes gradient on a dataset
def find_grad(x,y,W,b):
	W_grad = []
	b_grad = []
	for i in range(len(x)):
		total_1 = np.zeros(W.shape)
		bias_1 = np.zeros(b.shape)
		loss = 0 
		for j in range(len(x[i])):
			pred =  layer(W,x[i][j],b)
			bias_1 =bias_1+2*(pred-y[i][j])
			total_1=total_1+2*(pred-y[i][j])*x[i][j]
		W_grad.append(total_1/len(x[i]))
		b_grad.append(bias_1/len(x[i]))
	W_grad = np.array(W_grad)
	b_grad = np.array(b_grad)
	return (W_grad,b_grad)	

#### receives coded partial grads from slaves. Decodes the grads
def recv_grad():
	info = MPI.Status()
	W_update = []
	b_update = []
	recv_workers = []
	while(len(set(recv_workers)) < 2):
		# print(comm.recv(source=MPI.ANY_SOURCE,status=info))
		(temp_W,temp_b) = comm.recv(source=MPI.ANY_SOURCE,status=info)
		W_update.append(temp_W)
		b_update.append(temp_b)
		recv_workers.append((info.Get_source()-1)%3)
	recv = sum(set(recv_workers))
	a = A[total-recv][np.nonzero(A[total-recv])]
	W_update = np.array(W_update)/num_workers
	b_update = np.array(b_update)/num_workers
	W_grad = a[0]*W_update[0] + a[1]*W_update[1]
	b_grad = a[0]*b_update[0] + a[1]*b_update[1]
	return (W_grad,b_grad)


#### receives coded partial grads from slaves. Decodes the grads
def recv_grad2():
	info = MPI.Status()
	W_d1_update = []
	b_d1_update = []
	W_d2_update = []
	b_d2_update = []
	recv_workers = []
	while(len(set(recv_workers)) < 2):
		(W_grad_d1,b_grad_d1,W_grad_d2,b_grad_d2) = comm.recv(source=MPI.ANY_SOURCE,status=info)
		W_d1_update.append(W_grad_d1)
		b_d1_update.append(b_grad_d1)
		W_d2_update.append(W_grad_d2)
		b_d2_update.append(b_grad_d2)
		recv_workers.append((info.Get_source()-1)%3)
	recv = sum(set(recv_workers))
	a = A[3-recv][np.nonzero(A[3-recv])]
	W_d1_update = np.array(W_d1_update)/num_workers
	b_d1_update = np.array(b_d1_update)/num_workers
	W_d2_update = np.array(W_d2_update)/num_workers
	b_d2_update = np.array(b_d2_update)/num_workers
	
	W_grad_d1 = a[0]*W_d1_update[0] + a[1]*W_d1_update[1]
	b_grad_d1 = a[0]*b_d1_update[0] + a[1]*b_d1_update[1]
	W_grad_d2 = a[0]*W_d2_update[0] + a[1]*W_d2_update[1]
	b_grad_d2 = a[0]*b_d2_update[0] + a[1]*b_d2_update[1]
	
	return (W_grad_d1,b_grad_d1,W_grad_d2,b_grad_d2)

total_time = 0
for epoch in range(num_epochs): 
	if rank == 0:
		workers = tree[str(rank)]
		compalloc(data,W,b,rank)
		start = time.time()
		(W_grad,b_grad) = recv_grad()
		W = W - learning_rate*W_grad/num_workers
		b = b - learning_rate*b_grad/num_workers
		end = time.time()
		if epoch >  1:
			total_time = total_time + end - start
	else:
		parent = int((rank-1)/3)
		if rank < 4:
			row_b = (rank-1)%3
			b1 = B[row_b][np.nonzero(B[row_b])]
			destination = int((rank-1)/3)
			workers = tree[str(rank)]
			(x,y,W,b) = comm.recv(source = parent)
			partition_length = int(0.4*len(x[0]))
			x_store = [x[0][:partition_length] , x[1][:partition_length]]
			y_store = [y[0][:partition_length] , y[1][:partition_length]]
			x_send =  [x[0][partition_length:] , x[1][partition_length:]]
			y_send =  [y[0][partition_length:] , y[1][partition_length:]]
			compalloc2(x_send,y_send,W,b,rank)
			
			(W_grad_store,b_grad_store) = find_grad(x_store,y_store,W,b)
			(W_grad_d1,b_grad_d1,W_grad_d2,b_grad_d2) = recv_grad2()
			
			W_grad_store = b1[0]*W_grad_store[0] + b1[1]*W_grad_store[1]
			b_grad_store = b1[0]*b_grad_store[0] + b1[1]*b_grad_store[1]
	
			W_grad_send = b1[0]*W_grad_d1 + b1[1]*W_grad_d2
			b_grad_send = b1[0]*b_grad_d1 + b1[1]*b_grad_d2
			
			W_grad = 0.6*W_grad_send + 0.4*W_grad_store
			b_grad = 0.6*b_grad_send + 0.4*b_grad_store
			wait = np.random.exponential(beta)
			time.sleep(wait)
			comm.send((W_grad,b_grad),dest=destination) 
			
		if rank >= 4:
			row_b = (rank-1)%3
			b1 = B[row_b][np.nonzero(B[row_b])]
			destination = int((rank-1)/3)
			(x1,x2,y1,y2,W,b) = comm.recv(source = parent)
			(W_grad_d1,b_grad_d1) = find_grad(x1,y1,W,b)  ### gradients on D1
			(W_grad_d2,b_grad_d2) = find_grad(x2,y2,W,b)  ### gradients on D2
			
			coded_W_grad_d1 = b1[0]*W_grad_d1[0] + b1[1]*W_grad_d1[1]
			coded_b_grad_d1 = b1[0]*b_grad_d1[0] + b1[1]*b_grad_d1[1]
			coded_W_grad_d2 = b1[0]*W_grad_d2[0] + b1[1]*W_grad_d2[1]
			coded_b_grad_d2 = b1[0]*b_grad_d2[0] + b1[1]*b_grad_d2[1]
			
			wait = np.random.exponential(beta)
			time.sleep(wait)
			comm.send((coded_W_grad_d1,coded_b_grad_d1,coded_W_grad_d2,coded_b_grad_d2),dest=destination)

	time.sleep(0.1)

if rank == 0:
	print(total_time)