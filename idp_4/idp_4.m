g=2;
p=1;
while g<51
w1=(rand(4,g)-.5)/10;
w2=(rand(g,1)-.5)/10;
for i=1:100
    k = randperm(742, 594);
Data1(:,:,i) = Data(k, :);
r         = true(1,742);
r(k)      = false;
Data2(:,:,i) =Data(r, :);
end
for t=1:100
x1_in = Data1(1:594,(1:3),t);
mu=mean(x1_in);
st=std(x1_in);
x_in=(Data1(:,(1:3),t)-mu(:,1))/st(:,1);
bias=ones(594,1);
x_in=[x_in bias];
x1_out=Data1(:,4,t);
muo=mean(x1_out);
sto=std(x1_out);
x_out=(Data1(:,4,t)-muo(:,1))/sto(:,1);
j=0;
    k=0;
for i=1:10000
    y1=(x_in*w1);
    h1=tanh(y1);
    y2=(h1*w2);
    o=(tanh(y2));
    error=o-x_out;
        w2=w2-((h1'*(error.*(1-o.^2)).*.01)./594);
        err1=error*w2';
        w1=w1-(x_in'*(err1.*(1-h1.^2).*.01)./594);
end
x_pin=Data2(:,1:3,t);
mu=mean(x_pin);
st=std(x_pin);
x_pin=(x_pin(:,:)-mu(:,1))./st(:,1);
x_pin=[x_pin ones(148,1)];
h1=tanh(x_pin*w1);
o=tanh(h1*w2);
errf1=o*sto+muo-Data2(:,4);
x_pin=Data1(:,1:3);
mu=mean(x_pin);
st=std(x_pin);
x_pin=(x_pin(:,:)-mu(:,1))./st(:,1);
x_pout=Data1(:,4);
x_pin=[x_pin ones(594,1)];
h1=tanh(x_pin*w1);
o=tanh(h1*w2);
errf2=o*sto+muo-Data1(:,4);
msetr(t,p)=sum(errf2.^2)/148;
mintr(t,p)=min(abs(errf2));
maxtr(t,p)=max(abs(errf2));
msete(t,p)=sum(errf1.^2)/594;
minte(t,p)=min(abs(errf1));
maxte(t,p)=max(abs(errf1));
end
if g<10
    g=g+2;
else
    g=g+5;
end
    p=p+1;
end