#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 100005
int n,m;
int fa[MAXN][20],lev[MAXN],cnt[MAXN];
struct Edge
{int x;Edge*next;}edge[MAXN];
int Log(int x)
{
	int j;
	for(j=0;(1<<j)<=x;j++);
	return j-1;
}
void dfs(int node,int level)
{
	lev[node]=level;
	int count=1;
	for(Edge *p=edge[node].next;p;p=p->next)
		if(!lev[p->x])
		{
			fa[p->x][0]=node;
			dfs(p->x,level+1);
			count+=cnt[p->x];
		}
	cnt[node]=count;
}
int LCA(int x,int y)
{
	if(lev[x]<lev[y])
		swap(x,y);
	if(lev[x]>lev[y])
		for(int j=Log(lev[x]);j>=0;j--)
			if(lev[x]-(1<<j)>=lev[y])
				x=fa[x][j];
	if(x==y)return x;
	for(int j=Log(lev[x]);j>=0;j--)
		if(fa[x][j]!=-1&&fa[x][j]!=fa[y][j])
			x=fa[x][j],y=fa[y][j];
	return fa[x][0];
}
int main()
{
	scanf("%d",&n);
	for(int i=1,a,b;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		Edge *p=new Edge;
		p->x=b;
		p->next=edge[a].next;
		edge[a].next=p;
		p=new Edge;
		p->x=a;
		p->next=edge[b].next;
		edge[b].next=p;
	}
	memset(fa,-1,sizeof fa);
	fa[1][0]=0;
	dfs(1,1);
	for(int j=1;(1<<j)<=n;j++)
		for(int i=1;i<=n;i++)
			if(fa[i][j-1]!=-1)
				fa[i][j]=fa[fa[i][j-1]][j-1];
	scanf("%d",&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		if(a==b)
			printf("%d\n",n);
		else if(lev[a]==lev[b])
		{
			int t=LCA(a,b);
			for(int j=Log(lev[a]);j>=0;j--)
				if(lev[a]-(1<<j)>=lev[t]+1)
					a=fa[a][j];
			for(int j=Log(lev[b]);j>=0;j--)
				if(lev[b]-(1<<j)>=lev[t]+1)
					b=fa[b][j];
			printf("%d\n",n-cnt[a]-cnt[b]);
		}
		else
		{
			int t=LCA(a,b);
			if((lev[a]-lev[t]+lev[b]-lev[t])&1)
				printf("0\n");
			else
			{
				int l=(lev[a]-lev[t]+lev[b]-lev[t])>>1;
				if(lev[a]>lev[b])
				{
					l=lev[a]-l;
					for(int j=Log(lev[a]);j>=0;j--)
						if(lev[a]-(1<<j)>=l+1)
							a=fa[a][j];
					printf("%d\n",cnt[fa[a][0]]-cnt[a]);
				}
				else
				{
					l=lev[b]-l;
					for(int j=Log(lev[b]);j>=0;j--)
						if(lev[b]-(1<<j)>=l+1)
							b=fa[b][j];
					printf("%d\n",cnt[fa[b][0]]-cnt[b]);
				}
			}
		}
	}
	return 0;
}
