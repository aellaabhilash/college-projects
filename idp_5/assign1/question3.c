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
void add(){
	double a,b;
	printf("enter 1st number");
    scanf("%lf",&a);
    printf("enter 2nd number");
    scanf("%lf",&b);
    int16_t m,n;
    int32_t o;
    double_t r;
    int c,d,e;
    double p,q,re1,re2;
    
    re1=(log(a)/log(2));
    re2=(log(b)/log(2));
    if(roundf(re1)==re1&&a>1){
		c=a/2;
		}
		else{
    c=(a/2)+1;
}
    if(roundf(re2)==re2&&b>1){
		d=b/2;
		}
		else{
    d=(b/2)+1;
        }
    e=max(c,d);    
    p=round(a*(pow(2,14-e)));
    q=round(b*(pow(2,14-e)));
	m=(int16_t)(p);
	n=(int16_t)(q);
	o=m+n;
    r=(double)(o/(pow(2,14-e)));

	printf("%lf",r);
	
	}
	void sub(){
	double a,b;
	printf("enter 1st number");
    scanf("%lf",&a);
    printf("enter 2nd number");
    scanf("%lf",&b);
    int16_t m,n;
    int32_t o;
    double_t r;
    int c,d,e;
    double p,q,re1,re2;
    
    re1=(log(a)/log(2));
    re2=(log(b)/log(2));
    if(roundf(re1)==re1&&a>1){
		c=a/2;
		}
		else{
    c=(a/2)+1;
}
    if(roundf(re2)==re2&&b>1){
		d=b/2;
		}
		else{
    d=(b/2)+1;
        }
    e=max(c,d);
    
    p=round(a*(pow(2,15-e)));
    q=round(b*(pow(2,15-e)));
	m=(int16_t)(p);
	n=(int16_t)(q);
	o=m-n;
	r=(double)(o/(pow(2,15-e)));

	printf("%lf",r);
	
	}
int main(){
	int n;
	printf("enter 1 to add numbers,2 to subtrect");
	scanf("%d",&n);
	if(n==1){
		add();
		}
	else{
		sub();
		}
	return 0;
	}
