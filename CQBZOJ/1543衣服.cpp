#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#define MAXN 100100
using namespace std;
int a[MAXN],n,k;
bool check(int t)
{
	int kt=0;
	for(int i=1;i<=n;i++)
		if(a[i]>t)
		{
			int p=(a[i]-t-1)/(k-1)+1;
			kt+=p;
		}
	return kt<=t;
}
int main()
{
	int L=0,R=0,mid;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		R=max(R,a[i]);
	}
	scanf("%d",&k);
	if(k==1)
	{printf("%d\n",R);return 0;}
	L=(R-1)/k+1;
	while(1)
	{
		mid=(L+R)/2;
		if(L==R)break;
		if(check(mid))
			R=mid;
		else
			L=mid+1;
	}
	printf("%d\n",mid);
	return 0;
}
