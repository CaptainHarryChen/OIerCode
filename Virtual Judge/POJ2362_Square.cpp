#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int T,n,num[23],S;
bool vis[23];
bool dfs(int group,int s,int k)
{
	if(group==3)
		return 1;
	for(int i=k;i>=1;i--)
		if(!vis[i]&&s+num[i]<=S)
		{
			vis[i]=1;
			if(s+num[i]<S)
			{if(dfs(group,s+num[i],i-1))return 1;}
			else
			{if(dfs(group+1,0,n))return 1;}
			vis[i]=0;
		}
	return 0;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		S=0;
		int max_l=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&num[i]);
			S+=num[i];
			max_l=max(max_l,num[i]);
		}
		if(n<4||S%4!=0)
		{printf("no\n");continue;}
		S/=4;
		if(max_l>S)
		{printf("no\n");continue;}
		memset(vis,0,sizeof vis);
		sort(num+1,num+n+1);
		if(dfs(0,0,n))
			printf("yes\n");
		else
			printf("no\n");
	}
	return 0;
}
