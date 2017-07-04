#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int S,n,num[70];
bool vis[70];
bool dfs(int dep,int s,int k)
{
	if(dep==n)return 1;
	if(s==0)
	{
		int i;
		for(i=n;vis[i];i--);
		vis[i]=1;
		if(dfs(dep+1,num[i],i-1))return 1;
		vis[i]=0;
		return 0;
	}
	if(s==S)
	{
		if(dep==n)
			return 1;
		if(dfs(dep,0,0))
			return 1;
		return 0;
	}
	int same=-1;
	for(int i=k;i>=1;i--)
		if(!vis[i]&&num[i]!=same&&s+num[i]<=S)
		{
			vis[i]=1;
			same=num[i];
			if(dfs(dep+1,s+num[i],i-1))
				return 1;
			vis[i]=0;
		}
	return 0;
}
int main()
{
	while(1)
	{
		scanf("%d",&n);
		if(n==0)break;
		int sum=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&num[i]);
			sum+=num[i];
		}
		sort(num+1,num+n+1);
		for(S=num[n];S<=sum;S++)
		{
			if(sum%S!=0)continue;
			memset(vis,0,sizeof vis);
			if(dfs(0,0,n))
			{printf("%d\n",S);break;}
		}
	}
	return 0;
}
