#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define MAXN 505
using namespace std;
int N,M,W[MAXN],B[MAXN*2],book[MAXN],b,wans;
bool vis[MAXN];
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
		scanf("%d",&W[i]);
	for(int i=1;i<=M;i++)
	{
		scanf("%d",&B[i]);
		if(!vis[B[i]])
		{
			book[++b]=B[i];
			vis[B[i]]=1;
		}
	}
	for(int i=1;i<=N;i++)
		if(!vis[i])
			book[++b]=i;
	for(int i=1,j,t;i<=M;i++)
	{
		for(j=1;book[j]!=B[i];j++);
		t=book[j];
		for(int k=j-1;k>0;k--)
		{
			wans+=W[book[k]];
			book[k+1]=book[k];
		}
		book[1]=t;
	}
	printf("%d\n",wans);
	return 0;
}
