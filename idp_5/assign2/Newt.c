#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int max(int a,int b){
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}
float add(float a,float b){
	
    int16_t m,n;
    int32_t o;
    float r;
    int c,d,e;
    double p,q,re1,re2;
    float l=a,u=b;
    if(a<0){
		l=-a;
		}	
	if(b<0){
		u=-b;
		}
	if(a<=1&&a>=-1){
		c=1;
		}
	if(b<=1){
		d=1;
		}
	if(l>1){
    re1=(log(l)/log(2));
    }
    if(u>1){
    re2=(log(u)/log(2));
    }
    if(l>1){
    if(roundf(re1)==re1){
		c=round(re1)+1;
		}
		else if (roundf(re1)>re1){
    c=round(re1);
}
else{
	
	c=round(re1)+1;
	}
}
if(u>1){
     if(roundf(re2)==re2){
		d=round(re2)+1;
		}
		else if (roundf(re2)>re2){
    d=round(re2);
}
else{
	
	d=round(re2)+1;
	}
}
    printf("%d %d\n",c,d);
    e=max(c,d);    
    p=round(a*(pow(2,14-e)));
    q=round(b*(pow(2,14-e)));
	m=(int16_t)(p);
	n=(int16_t)(q);
	o=m+n;
    r=(float)(o/(pow(2,14-e)));
    //printf("%f",r);
	return r;
	
	}
	
	float sub(float a, float b){
	
    int16_t m,n;
    int32_t o;
    float r;
    int c,d,e;
    double p,q,re1,re2;
    float l=a,u=b;
    if(a<0){
		l=-a;
		}	
	if(b<0){
		l=-b;
		}
	if(a<=1&&a>=-1){
		c=1;
		}
	if(b<=1){
		d=1;
		}
	if(l>1){
    re1=(log(l)/log(2));
    }
    if(u>1){
    re2=(log(u)/log(2));
    }
    if(l>1){
    if(roundf(re1)==re1){
		c=round(re1)+1;
		}
		else if (roundf(re1)>re1){
    c=round(re1);
}
else{
	
	c=round(re1)+1;
	}
}
if(u>1){
     if(roundf(re2)==re2){
		d=round(re2)+1;
		}
		else if (roundf(re2)>re2){
    d=round(re2);
}
else{
	
	d=round(re2)+1;
	}
}
	
    e=max(c,d);
    
    p=round(a*(pow(2,15-e)));
    q=round(b*(pow(2,15-e)));
	m=(int16_t)(p);
	n=(int16_t)(q);
	o=m-n;
	r=(double)(o/(pow(2,15-e)));

	return r;
	
	}
float mul(float a,float b){
	
    int16_t m,n;
    int32_t o;
    float k=1;
    float r;
    int c,d,e;
    float l=a,u=b;
    double p,q,re1,re2;
    if(l<0){
	l=-l;
		}
	if(u<0){
		u=-u;
		}
	if(a<0&&b>0){
		k=-1;
		}
		if(a>0&&b<0){
			k=-1;
			}
	if(l<=1){
		c=1;
		}
	if(u<=1){
		d=1;
		}
	if(l>1){
    re1=(log(l)/log(2));
    }
    if(u>1){
    re2=(log(u)/log(2));
    }
    if(l>1){
    if(roundf(re1)==re1){
		c=round(re1)+1;
		}
		else if (roundf(re1)>re1){
    c=round(re1);
}
else{
	
	c=round(re1)+1;
	}
}
if(u>1){
     if(roundf(re2)==re2){
		d=round(re2)+1;
		}
		else if (roundf(re2)>re2){
    d=round(re2);
}
else{
	
	d=round(re2)+1;
	}
}
	e=c+d;
	//printf("%d %d %d %f\n",e,c,d,b);
    p=round(l*(pow(2,14-c)));
    q=round(u*(pow(2,14-d)));
	m=(int16_t)(p);
	n=(int16_t)(q);
	o=m*n;
	r=(double)(o/(pow(2,(28-e))));
    r=r*k;
    //printf("%f\n",r);
	return r;
	
	}

float div1(float a,float b){
	
    int32_t m,n;
    int32_t o;
    float k=1;
    float r;
    int c,d,e;
    float l=a,u=b;
    double p,q,re1,re2;
    if(l<0){
	l=-l;
		}
	if(u<0){
		u=-u;
		}
	if(a<0&&b>0){
		k=-1;
		}
		if(a>0&&b<0){
			k=-1;
			}
	if(l<=1){
		c=1;
		}
	if(u<=1){
		d=1;
		}
	if(l>1){
    re1=(log(l)/log(2));
    }
    if(u>1){
    re2=(log(u)/log(2));
    }
    if(l>1){
    if(roundf(re1)==re1){
		c=round(re1)+1;
		}
		else if (roundf(re1)>re1){
    c=round(re1);
}
else{
	
	c=round(re1)+1;
	}
}
if(u>1){
     if(roundf(re2)==re2){
		d=round(re2)+1;
		}
		else if (roundf(re2)>re2){
    d=round(re2);
}
else{
	
	d=round(re2)+1;
	}
}
	e=max(c,d);
    
    p=round(a*(pow(2,30-e)));
    q=round(b*(pow(2,14-e)));
    printf("%lf\n",p/q);
	m=(int32_t)(p);
	n=(int32_t)(q);
	o=m/n;
	r=(double)(o/pow(2,16));
	return r;
	
	}

float fun(float x){
	float r;
	r=add(mul(x,x),add(mul(-2,x),1));
	return r;
	}
float der( float x){
	float der,x1,x2,y1,y2,t=0.01;
	x1=x;
	x2=add(x1,t);
	y1=fun(x1);
	y2=fun(x2);
	der=mul(sub(y2,y1),100);
	return der;
	}
void root(){
	float x=0;
	int i=0;
	while(i==0){
	if (fun(x)<0.00000001&&fun(x)>-0.000000001){
		printf("The root of equation is %f",x);
		i=1;
		}
	else{
		x=sub(x,(div1(fun(x),der(x))));
		}
	}
}

int main(){	
   root();
	return 0;
 }
