
# coding: utf-8

# In[1]:


import os 
import time 

os.environ["OPENBLAS_NUM_THREADS"] = '1'

import numpy as np 
from mpi4py import MPI 
import time

# In[2]:


comm = MPI.COMM_WORLD
rank = comm.Get_rank()
num_workers = comm.Get_size()-1

# In[3]:

np.random.seed(42)
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

def layer(w,x,b):
    out = np.matmul(w.T,x)+b
    return out

# derivative of sum of square error function
def mse(y_true,y_pred):
    return (y_true-y_pred)**2


def partition_data(data,n):
    return np.split(data,n)

def create_B_matrix(s,n):
    ### input s,n 
    ### output B(n,n) with s+1 non zero elements in each row
    H = np.random.randn(s,n)
    print(H.shape)
    H[:,n-1] = -np.sum(H[:,0:n-1],axis=1)
    B = np.zeros((n,n))
    for i in range(n):
        j = np.arange(i,s+i+1)%n
        B[i,j] = np.append(np.array([1]), -np.matmul(np.linalg.pinv(H[:,j[1:s+1]]),H[:,j[0]]))
    return B

X_orig=np.array([[1,0],[0,1],[1,1],[0,0]])
y_orig=np.array([1,1,1,0])
number_train_samples = 1200
number_nodes = 1
learning_rate = 1e-2
num_epochs = 500
beta = 0.02
data=get_data(X_orig,y_orig,number_train_samples)
W1=np.random.normal(0,1,(2,1))
b1=np.random.normal(0,1,(1,1))

X = partition_data(data[0],num_workers)
y = partition_data(data[1],num_workers)

total_time = 0
for epoch in range(num_epochs):
	
	if rank == 0:
		for i in range(len(X)):
			comm.send((X[i],y[i],W1,b1),dest=i+1)
		
		gradients_W = np.zeros(W1.shape)
		gradients_b = np.zeros(b1.shape)

		start = time.time()
		for i in range(num_workers):
			(W_update,b_update) = comm.recv(source=i+1)
			gradients_W = gradients_W + W_update
			gradients_b = gradients_b + b_update
		
		W1 = W1 - learning_rate*gradients_W/len(X)
		b1 = b1 - learning_rate*gradients_b/len(X)
		end = time.time()
		if epoch > 1:
			total_time = total_time + end - start
	else:
		(x,y,W,b) = comm.recv(source=0)
		total_1 = np.zeros(W.shape)
		bias_1 = np.zeros(b.shape)
		loss = 0 
		for i in range(len(x)):
			pred =  layer(W,x[i],b)
			bias_1 =bias_1+2*(pred-y[i])
			total_1=total_1+2*(pred-y[i])*x[i]
		bias_1 = bias_1/len(x)
		total_1 = total_1/len(x)
		wait = np.random.exponential(beta)
		time.sleep(wait)
		comm.send((total_1,bias_1),dest=0)
# In[ ]:

if rank == 0:
	print(total_time)