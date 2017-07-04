#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
int n,k,count,nm,q,quanzhi[12]={1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800};
char tnum[10];
bool f[400000],shuzi[10];
int zhuanhuan(char x[])
{
	int cnt=0,sum=0;
	bool ff[10]={0};
	for(int i=0;i<10;i++)
	{
		cnt=0;
		for(int j=i+1;j<9;j++)
			if(x[j]<x[i]&&ff[j]==0)
				cnt++;
		ff[i]=1;
		sum+=cnt*quanzhi[n-i-1];
	}
	return sum;
}
void dfs(int p)
{
	if(p==n)
	{
		int s=zhuanhuan(tnum);
		if(f[s]==0)
			count++;
		f[s]=1;
		if(count==k)
		{
			for(int i=0;i<n;i++)
				printf("%d",tnum[i]);
			printf("\n");
			exit(0);
		}
		return;
	}
	for(int i=0;i<10;i++)
		if(shuzi[i]!=0)
		{
			tnum[q++]=i;
			shuzi[i]=0;
			dfs(p+1);
			shuzi[i]=1;
			tnum[--q]=0;
		}
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		shuzi[i]=1;
	dfs(0);
	return 0;
}
