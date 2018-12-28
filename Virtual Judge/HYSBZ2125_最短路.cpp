#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=20005,MAXLOG=16;

struct Edge
{
	int v,w,id;
	Edge(){}
	Edge(int _v,int _w):v(_v),w(_w){}
};

int N,M,Q,CC;
vector<Edge> G[MAXN],T[MAXN];

void AddEdge(vector<Edge> g[],int u,int v,int w)
{
	g[u].push_back(Edge(v,w));
	g[v].push_back(Edge(u,w));
}

int bck[MAXN],cir[MAXN],dfn[MAXN],low[MAXN],dep[MAXN],dfc;
int stk[MAXN],tp;

void Tarjan(int u=1,int f=0)
{
	dfn[u]=low[u]=++dfc;
	stk[++tp]=u;
	for(vector<Edge>::iterator e=G[u].begin();e!=G[u].end();e++)
	{
		int v=e->v;
		if(v==f)
            continue;
		if(!dfn[v])
		{
			dep[v]=dep[u]+e->w;
			Tarjan(v,u);
            low[u]=min(low[u],low[v]);
			if(low[v]==dfn[u])
			{
				CC++;
				cir[CC]=dep[stk[tp]]-dep[u]+bck[stk[tp]];
				do
				{
					AddEdge(T,CC,stk[tp],min(dep[stk[tp]]-dep[u],cir[CC]-dep[stk[tp]]+dep[u]));
					tp--;
				}while(stk[tp+1]!=v);
				AddEdge(T,u,CC,0);
			}
			else if(low[v]>dfn[u])
			{
				AddEdge(T,u,v,e->w);
				tp--;
			}
		}
		else if(dfn[v]<low[u])
        {
			low[u]=dfn[v];
			bck[u]=e->w;
        }
	}
}

int fa[MAXN][MAXLOG],dis[MAXN][MAXLOG],lev[MAXN];
void dfs(int u)
{
	for(vector<Edge>::iterator e=T[u].begin();e!=T[u].end();e++)
	{
		int v=e->v;
		if(v==fa[u][0])
			return;
		fa[v][0]=u;
		dis[v][0]=e->w;
		lev[v]=lev[u]+1;
		dfs(v);
	}
}
void InitLCA()
{
	dfs(1);
	for(int j=1;(1<<j)<CC;j++)
		for(int i=1;i<=CC;i++)
			if(lev[i]-(1<<j)>=0)
			{
				fa[i][j]=fa[fa[i][j-1]][j-1];
				dis[i][j]=dis[i][j-1]+dis[fa[i][j-1]][j-1];
			}
}

int QueryPath(int u,int v)
{
	if(lev[u]>lev[v])
		swap(u,v);
	int res=0;
	for(int j=MAXLOG-1;j>=0;j--)
		if(lev[v]-(1<<j)>=lev[u])
		{
			res+=dis[v][j];
			v=fa[v][j];
		}
	if(u==v)
		return res;
	for(int j=MAXLOG-1;j>=0;j--)
		if(lev[u]-(1<<j)>=0&&fa[u][j]!=fa[v][j])
		{
			res+=dis[u][j]+dis[v][j];
			u=fa[u][j];
			v=fa[v][j];
		}
	if(fa[u][0]<=N)
		return res+dis[u][0]+dis[v][0];
	res+=min(abs(dep[u]-dep[v]),cir[fa[u][0]]-abs(dep[u]-dep[v]));
	return res;
}

int main()
{
	scanf("%d%d%d",&N,&M,&Q);
	for(int i=1;i<=M;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		AddEdge(G,u,v,w);
	}

	CC=N;
	Tarjan();
	InitLCA();

	while(Q--)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		printf("%d\n",QueryPath(u,v));
	}

	return 0;
}
