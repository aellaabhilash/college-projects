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
    //printf("%d %d\n",c,d);
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

void correlation(float a[],float b[], int n, int m){
	float c[n+m];
	for(int i=n;i<m+n-1;i++){
       a[i]=0;
}
printf("correlation of two signals is :");
for(int i=m;i<n+m-1;i++){
b[i]=0;
}

for(int i=0;i<max(m,n);i++)
{
c[i]=0;
for(int j=0;j<max(m,n);j++)
{
c[i]+=a[j+i]*b[j];
}
printf("%f\n",c[i]);
}


}                      


	
	
	
int main(){
	int n,m;
	printf("enter number of elements in the first signal:");
	scanf("%d",&n);
	printf("enter number of elements in the second signal:");
	scanf("%d",&m);
	float a[m+n],b[m+n];
	printf("enter the numbers of first signal");
	for (int i=0;i<n;i++){
		scanf("%f",&a[i]);		
		}

	printf("enter the numbers of second signal");
	for (int i=0;i<m;i++){
		scanf("%f",&b[i]);		
		}	
	correlation(a,b,n,m);	
	
	return 0;
	}
