#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=300005,MAXM=300005;

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
Graph G,F;

int dfn[MAXN],low[MAXN],dfc;
int stk[MAXN],tp;
int blkid[MAXN],blkc;

void tarjan(int u,int fa=0)
{
	low[u]=dfn[u]=++dfc;
	stk[++tp]=u;
	for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
	{
		int v=e->v;
		if(v==fa)
			continue;
		if(!dfn[v])
		{
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
    {
        blkc++;
        do
        {
            blkid[stk[tp]]=blkc;
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
                F.AddEdge(blkid[u],blkid[v]);
        }
}

int dep[MAXN];
void dfs(int u,int fa=0)
{
    for(Graph::AdjEdge *e=F.adj[u];e;e=e->nxt)
    {
        int v=e->v;
        if(v==fa)
            continue;
        dep[v]=dep[u]+1;
        dfs(v,u);
    }
}

int FindDiameter()
{
    dep[1]=0;
    dfs(1);
    int mxid=1,mx=0;
    for(int i=1;i<=blkc;i++)
        if(mx<dep[i])
            mx=dep[i],mxid=i;
    dep[mxid]=0;
    dfs(mxid);
    for(int i=1;i<=blkc;i++)
        mx=max(mx,dep[i]);
    return mx;
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

    dfc=0;blkc=0;
    tarjan(1);
    MakeNewGraph();

    printf("%d\n",FindDiameter());

    return 0;
}
