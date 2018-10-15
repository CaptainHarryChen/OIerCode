#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=5005,MAXM=10005;

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
int ans=0;

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
			if(low[v]>dfn[u])
			{
				blkc++;
				do
				{
					blkid[stk[tp]]=blkc;
					tp--;
				}while(stk[tp+1]!=v);
			}
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
}
void dfs(int u,int fa=0)
{
	int cnt=0;
	for(Graph::AdjEdge *e=F.adj[u];e;e=e->nxt)
	{
		int v=e->v;
		if(v==fa)
			continue;
		cnt++;
		dfs(v,u);
	}
	ans+=(cnt==0||(fa==0&&cnt==1));
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
	blkc++;
	do
	{
		blkid[stk[tp]]=blkc;
		tp--;
	}while(tp);
	
	F.Clear();
	for(int u=1;u<=n;u++)
		for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
		{
			int v=e->v;
			if(blkid[u]!=blkid[v])
				F.AddEdge(blkid[u],blkid[v]);//,printf("%d %d\n",blkid[u],blkid[v]);
		}
	dfs(1);
	if(blkc==1)
		ans=0;
	else
		ans=(ans+1)/2;
	
	printf("%d\n",ans);

    return 0;
}
