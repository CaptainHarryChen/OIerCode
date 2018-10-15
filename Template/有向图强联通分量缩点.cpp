#include<cstdio>
#include<bitset>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=2005,MAXM=4000005;

struct Graph
{
    struct AdjEdge
    {
        int v;
        AdjEdge *nxt;
    }edges[MAXM],*adj[MAXN],*edges_it;

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
Graph G,F;
bitset<MAXN> dp[MAXN];

int dfn[MAXN],low[MAXN],dfc;
int stk[MAXN],tp;
bool instk[MAXN];
int blkid[MAXN],blkc;

void tarjan(int u)
{
	low[u]=dfn[u]=++dfc;
	stk[++tp]=u;
	instk[u]=true;
	for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
	{
		int v=e->v;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(instk[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
    {
        blkc++;
        do
        {
            blkid[stk[tp]]=blkc;
            instk[stk[tp]]=false;
            tp--;
        }while(stk[tp+1]!=u);
    }
}

void MakeNewGraph()
{
    F.Clear();
    for(int u=1;u<=n;u++)
        for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
        {
            int v=e->v;
            if(blkid[u]!=blkid[v])
            {
                F.AddEdge(blkid[u],blkid[v]);
                printf("%d->%d\n",blkid[u],blkid[v]);
            }
        }
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
    }

    dfc=0;blkc=0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i);
    MakeNewGraph();

    return 0;
}
