#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 300005
int n,q;
int fa[MAXN],del_edge[MAXN];
int order[MAXN][2],ans[MAXN];
bool vis[MAXN];
int root(int x)
{
	if(vis[x])return -1;
	if(fa[x]==0)return x;
	vis[x]=1;
	int r=root(fa[x]);
	vis[x]=0;
	if(r==-1)return -1;
	return fa[x]=r;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&fa[i]);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&order[i][0],&order[i][1]);
		if(order[i][0]==2)
		{
			del_edge[order[i][1]]=fa[order[i][1]];
			fa[order[i][1]]=0;
		}
	}
	for(int i=1;i<=n;i++)
		root(i);
	for(int i=q;i>0;i--)
	{
		if(order[i][0]==1)
		{
			int r=root(order[i][1]);
			ans[i]=r;
		}
		else
			fa[order[i][1]]=del_edge[order[i][1]];
	}
	for(int i=1;i<=q;i++)
		if(ans[i]==-1)
			printf("CIKLUS\n");
		else if(ans[i]!=0)
			printf("%d\n",ans[i]);
	return 0;
}
