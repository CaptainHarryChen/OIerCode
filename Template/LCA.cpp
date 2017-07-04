#include<cstdio>
#include<cstring>
#include<iostream>
#define MAXN 100005
int N,Q;
struct Edge
{
	int id;
	Edge *next;
	Edge():next(NULL){}
	Edge(int a):id(a),next(NULL){}
}edge[MAXN];
void add_edge(int a,int b)
{
	Edge *p=new Edge(b);
	p->next=edge[a].next;
	edge[a].next=p;
}
namespace LCA
{
	int fa[MAXN][22],lev[MAXN];
	void dfs(int id,int level)
	{
		lev[id]=level;
		for(Edge *p=edge[id].next;p;p=p->next)
			if(!lev[p->id])
			{
				dfs(p->id,level+1);
				fa[p->id][0]=id;
			}
	}
	void init()
	{
		for(int j=1;(1<<j)<=N;j++)
			for(int i=1;i<=N;i++)
				if(fa[i][j-1])
					fa[i][j]=fa[fa[i][j-1]][j-1];
	}
	int solve(int a,int b)
	{
		if(lev[a]>lev[b])std::swap(a,b);
		for(int j=20;j>=0;j--)
			if(lev[b]-(1<<j)>=lev[a])
				b=fa[b][j];
		if(a==b)return a;
		for(int j=20;j>=0;j--)
			if(fa[a][j]&&fa[b][j]&&fa[a][j]!=fa[b][j])
				a=fa[a][j],b=fa[b][j];
		return fa[a][0];
	}
}
int main()
{
	freopen("LCA_data.in","r",stdin);
	scanf("%d%d",&N,&Q);
	for(int i=1,x,y;i<N;i++)
	{
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	LCA::dfs(1,1);
	LCA::init();
	for(int i=1,a,b;i<=Q;i++)
	{
		scanf("%d%d",&a,&b);
		printf("%d\n",LCA::solve(a,b));
	}
	return 0;
}
