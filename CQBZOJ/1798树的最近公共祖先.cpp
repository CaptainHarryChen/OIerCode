#include<cstdio>
#include<vector>
#include<iostream>
#include<cmath>
using namespace std;
#define MAXN 20005
int N,fa[MAXN],deep[MAXN],H,nr,root,P[MAXN],Q;
vector<int>sons[MAXN];
void dfs(int k)
{
	if(deep[k]<nr)
		P[k]=root;
	else
		if(!(deep[k]%nr))
			P[k]=fa[k];
		else
			P[k]=P[fa[k]];
	for(int i=0;i<(int)sons[k].size();i++)
		dfs(sons[k][i]);
}
int LCA(int x,int y)
{
	while(P[x]!=P[y])
		if(deep[x]>deep[y])
			x=P[x];
		else
			y=P[y];
	while(x!=y)
		if(deep[x]>deep[y])
			x=fa[x];
		else
			y=fa[y];
	return x;
}
int main()
{
	scanf("%d",&N);
	for(int i=1,r,c;i<=N;i++)
	{
		scanf("%d:(%d)",&r,&c);
		for(int j=1,s;j<=c;j++)
		{
			scanf("%d",&s);
			sons[r].push_back(s);
			fa[s]=r;
			deep[s]=deep[r]+1;
		}
	}
	for(int i=1;i<=N;i++)
	{
		H=max(H,deep[i]);
		if(fa[i]==0)root=i;
	}
	nr=sqrt(H);
	dfs(root);
	scanf("%d",&Q);
	for(int i=1,x,y;i<=Q;i++)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",LCA(x,y));
	}
	return 0;
}
