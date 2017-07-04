#include<cstdio>
#include<iostream>
using namespace std;
int a,b,c;
double x;
double mabs(double x)
{
	if(x<0)
		return -x;
	return x;
}
void f(double l,double r)
{
	if(mabs(l-r)<0.000001)
	{
		x=(l+r)/2;
		return;
	}
	double mid=(l+r)/2,s=a;
	for(int i=1;i<=b;i++)
		s=s*(1+mid)-c;
	if(s==0)
	{
		x=mid;
		return;
	}
	if(s<0)
	{
		f(mid,r);
		return;
	}
	if(s>0)
	{
		f(l,mid);
		return;
	}
}
int main()
{
	scanf("%d%d%d",&a,&b,&c);
	f(0,1);
	printf("%.3lf%%\n",x*100);
	return 0;
}
