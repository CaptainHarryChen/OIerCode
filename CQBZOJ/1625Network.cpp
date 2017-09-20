#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXM=500005;
struct Edge
{
	int v;
	Edge *next;
};
struct Graph
{
	Edge E[MAXM],*V[MAXN],*cur;
	Graph()
	{clear();}
	void clear()
	{
		memset(V,0,sizeof V);
		cur=E;
	}
	void add_edge(int u,int v)
	{
		cur->v=v;
		cur->next=V[u];
		V[u]=cur++;
	}
};
Graph G,g;
bool vis[MAXN];
int stack[MAXN],top;
int blkid[MAXN],blkc,blksz[MAXN];
int outid[MAXN],inid[MAXN];
void dfs(int u)
{
	vis[u]=true;
	for(Edge *p=G.V[u];p;p=p->next)
		if(!vis[p->v])
			dfs(p->v);
	stack[++top]=u;
}
void rdfs(int u)
{
	blkid[u]=blkc;
	blksz[blkc]++;
	for(Edge *p=g.V[u];p;p=p->next)
		if(!blkid[p->v])
			rdfs(p->v);
}
void make_g(int N,int R)
{
	memset(vis,0,sizeof vis);
	dfs(R);
	while(top)
	{
		if(!blkid[stack[top]])
		{
			blkc++;
			rdfs(stack[top]);
		}
		top--;
	}
	g.clear();
	for(int u=1;u<=N;u++)
		for(Edge *p=G.V[u];p;p=p->next)
			if(blkid[u]!=blkid[p->v])
			{
				g.add_edge(blkid[u],blkid[p->v]);
				inid[blkid[p->v]]=p->v;
				outid[g.cur-g.E-1]=u;
			}
	inid[blkid[R]]=R;
}
int ans1[MAXN];
void solve1(int u)
{
	ans1[u]=blksz[u];
	for(Edge *p=g.V[u];p;p=p->next)
	{
		if(!ans1[p->v])
			solve1(p->v);
		ans1[u]+=ans1[p->v];
	}
}
int ans2[MAXN][2],cnt;
int dfn[MAXN],low[MAXN],dfc;
void solve2(int u,int opt)
{
	dfn[u]=low[u]=++dfc;
	bool flag=true;
	for(Edge *p=g.V[u];p;p=p->next)
	{
		int v=p->v;
		if(inid[u]==outid[p-g.E]&&flag)
			solve2(v,opt);
		else
			solve2(v,outid[p-g.E]);
		if(low[v]<low[u])
			flag=false;
		low[u]=min(low[u],low[v]);
	}
	if(low[u]==dfn[u])
	{
		ans2[++cnt][0]=inid[u];
		ans2[cnt][1]=opt;
		low[u]=dfn[blkid[opt]];
	}
}
int main()
{
	int N,M,R,u,v;
	scanf("%d%d%d",&N,&M,&R);
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d",&u,&v);
		G.add_edge(u,v);
		g.add_edge(v,u);
	}
	make_g(N,R);
	solve1(blkid[R]);
	for(int i=1;i<N;i++)
		printf("%d ",ans1[blkid[i]]);
	printf("%d\n",ans1[blkid[N]]);
	solve2(blkid[R],R);
	printf("%d\n",cnt-1);
	for(int i=1;i<cnt;i++)
		printf("%d %d\n",ans2[i][0],ans2[i][1]);
	return 0;
}
