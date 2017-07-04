#include<cstdio>
#include<iostream>
using namespace std;
int a,b,s;
double t;
void f(double x,double y)
{
	double mid=(x+y)/2;
	double t1=(s-mid)/a,t2=(mid-mid/b*a)/(a+b)+mid/b;
	if((t1>t2?t1-t2:t2-t1)<0.000001)
	{
		t=mid/b+(s-mid)/a;
		return;
	}
	if(t1>t2)
	{
		f(mid,y);
		return;
	}
	if(t1<t2)
	{
		f(x,mid);
		return;
	}
}
int main()
{
	scanf("%d%d%d",&s,&a,&b);
	f(0,s);
	printf("%.4lf\n",t);
	return 0;
}
