#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXM=500005;

struct Graph
{
    struct AdjEdge
    {
        int v;
        AdjEdge *nxt;
    }edges[MAXM*2],*adj[MAXN],*edges_it;

    void Clear()
    {
        memset(adj,0,sizeof adj);
        edges_it=edges;
    }
    void AddEdge(int u,int v)
    {
        edges_it->v=v;
        edges_it->nxt=adj[u];
        adj[u]=edges_it++;
    }
};

int n,m;
Graph G;
long long ans[MAXN];

int dfn[MAXN],low[MAXN],dfc;
int siz[MAXN];

void tarjan(int u,int fa=0)
{
	low[u]=dfn[u]=++dfc;
	siz[u]=1;
	int sum=n-1;
	for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
	{
		int v=e->v;
		if(v==fa)
			continue;
		if(!dfn[v])
		{
			tarjan(v,u);
			siz[u]+=siz[v];
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u])
			{
				sum-=siz[v];
				ans[u]+=2LL*siz[v]*sum;
			}
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
	ans[u]+=2LL*(n-1);
}

int main()
{
    scanf("%d%d",&n,&m);
	G.Clear();
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G.AddEdge(u,v);
        G.AddEdge(v,u);
    }

    tarjan(1);
	
	for(int i=1;i<=n;i++)
		printf("%lld\n",ans[i]);

    return 0;
}
