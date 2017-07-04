#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define MAXN 100100
#define INF 2000000000
using namespace std;
int n,m,num[MAXN];
int find(int l,int r,int k)
{
	int mid=(l+r)>>1;
	if(r-l==1)
	{
		if(k-num[l]<=num[r]-k)
			return num[l];
		return num[r];
	}
	if(k<num[mid])
		return find(l,mid,k);
	else if(k>num[mid])
		return find(mid,r,k);
	else
		return num[mid];
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
	num[0]=-INF;num[n+1]=INF;
	scanf("%d",&m);
	n++;
	for(int i=1,k;i<=m;i++)
	{
		scanf("%d",&k);
		printf("%d\n",find(0,n,k));
	}
	return 0;
}
