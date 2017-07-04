#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define MAXN 100100
using namespace std;
int n,m,num[MAXN];
void solve(int l,int r,int x)
{
	if(r-l<=1)
	{
		if(x+num[l]==m)
		{printf("%d %d\n",x,num[l]);exit(0);}
		else if(x+num[r]==m)
		{printf("%d %d\n",x,num[r]);exit(0);}
		return;
	}
	int mid=(l+r)/2;
	if(x+num[mid]==m)
	{
		printf("%d %d\n",x,num[mid]);
		exit(0);
	}
	else if(x+num[mid]>m)
		solve(l,mid-1,x);
	else
		solve(mid+1,r,x);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
	scanf("%d",&m);
	sort(num+1,num+n+1);
	for(int i=1;i<n;i++)
		solve(i+1,n,num[i]);
	printf("No\n");
	return 0;
}
