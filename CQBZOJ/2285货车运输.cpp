#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define MAXN 10005
#define MAXM 50005
int n,m,Q;
int fa[MAXN],level[MAXN];
int f[MAXN][20],g[MAXN][20];
struct Way
{
	int x,y,w;
}way[MAXM];
bool cmp(Way a,Way b){return a.w>b.w;}
int find(int x)
{return fa[x]==x?x:fa[x]=find(fa[x]);}
struct Edge
{
	int y,w;
	Edge *next;
	Edge(){}Edge(int a,int b):y(a),w(b),next(NULL){}
}edge[MAXN];
void add_edge(Way t)
{
	Edge *p=new Edge(t.y,t.w);
	p->next=edge[t.x].next;
	edge[t.x].next=p;
	p=new Edge(t.x,t.w);
	p->next=edge[t.y].next;
	edge[t.y].next=p;
}
void make_trees()
{
	for(int i=1;i<=n;i++)
		fa[i]=i;
	sort(way+1,way+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		int x=find(way[i].x),y=find(way[i].y);
		if(x!=y)
		{
			fa[x]=y;
			add_edge(way[i]);
		}
	}
}
void dfs(int x,int lev)
{
	level[x]=lev;
	for(int j=1;(1<<j)<lev;j++)
	{
		f[x][j]=f[f[x][j-1]][j-1];
		g[x][j]=min(g[x][j-1],g[f[x][j-1]][j-1]);
	}
	for(Edge *p=edge[x].next;p;p=p->next)
		if(!level[p->y])
		{
			f[p->y][0]=x;
			g[p->y][0]=p->w;
			dfs(p->y,lev+1);
		}
}
int lca(int a,int b)
{
	if(level[a]>level[b])
		swap(a,b);
	int ret=0x7FFFFFFF;
	for(int j=13;j>=0;j--)
		if(level[f[b][j]]>=level[a])
		{
			ret=min(ret,g[b][j]);
			b=f[b][j];
		}
	if(a==b)return ret;
	for(int j=13;j>=0;j--)
		if(f[a][j]!=f[b][j])
		{
			ret=min(ret,min(g[a][j],g[b][j]));
			a=f[a][j];b=f[b][j];
		}
	ret=min(ret,min(g[a][0],g[b][0]));
	return ret;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&way[i].x,&way[i].y,&way[i].w);
	make_trees();
	for(int i=1;i<=n;i++)
		if(!level[i])
			dfs(i,1);
	scanf("%d",&Q);
	for(int i=1,a,b;i<=Q;i++)
	{
		scanf("%d%d",&a,&b);
		if(find(a)!=find(b))
			printf("-1\n");
		else
			printf("%d\n",lca(a,b));
	}
	return 0;
}
