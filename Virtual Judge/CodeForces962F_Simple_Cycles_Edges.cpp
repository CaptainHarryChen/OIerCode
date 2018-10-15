#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXM=100005;

struct Graph
{
    struct AdjEdge
    {
        int v,id;
        AdjEdge *nxt;
    }edges[MAXM*2],*adj[MAXN],*edges_it;

    void Clear()
    {
        memset(adj,0,sizeof adj);
        edges_it=edges;
    }
    void AddEdge(int u,int v,int i)
    {
        edges_it->v=v;
		edges_it->id=i;
        edges_it->nxt=adj[u];
        adj[u]=edges_it++;
    }
};

pair<int,int> edges[MAXM];

int n,m;
Graph G;
bool ans[MAXM];

int dfn[MAXN],low[MAXN],dfc;
int stk[MAXN],tp;

bool used[MAXM];
set<int> vis;

void tarjan(int u)
{
	low[u]=dfn[u]=++dfc;
	for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
	{
	    if(used[e->id])
			continue;
        used[e->id]=true;
        stk[++tp]=e->id;
		int v=e->v;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u])
			{
				int tmp=tp;
				vis.clear();
				do
				{
				    vis.insert(edges[stk[tp]].first);
				    vis.insert(edges[stk[tp]].second);
					tp--;
				}while(stk[tp+1]!=e->id);
				if((int)vis.size()==(tmp-tp))
				{
					for(int i=tp+1;i<=tmp;i++)
                        ans[stk[i]]=true;
				}
			}
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
}

int main()
{
    scanf("%d%d",&n,&m);
	G.Clear();
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&edges[i].first,&edges[i].second);
        G.AddEdge(edges[i].first,edges[i].second,i);
        G.AddEdge(edges[i].second,edges[i].first,i);
    }

    for(int u=1;u<=n;u++)
        if(!dfn[u])
            tarjan(u);


	int cnt=0;
	for(int i=1;i<=m;i++)
		cnt+=ans[i];
	printf("%d\n",cnt);
	for(int i=1;i<=m;i++)
		if(ans[i])
			printf("%d ",i);
	puts("");

    return 0;
}
