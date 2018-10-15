#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<map>
#include<algorithm>
using namespace std;
const int MAXN=500005,MAXM=2000005;
typedef pair<int,int> Edge;

struct Graph
{
    struct AdjEdge
    {
        int v;
		bool vis;
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
		edges_it->vis=false;
        adj[u]=edges_it++;
    }
};

int N,M;
Edge E[MAXM];
map<Edge,int> id;

int nxt[MAXM],pre[MAXM],e[MAXM],v[MAXM];
int vis[MAXM];
int deg[MAXN];
Graph G;

void NIE()
{
	puts("NIE");
	exit(0);
}

int cnt;
void Eular(int u)
{
	for(Graph::AdjEdge *&e=G.adj[u];e;)
	{
		if(e->vis)
		{
			e=e->nxt;
			continue;
		}
		e->vis=true;
		cnt++;
		Eular(e->v);
	}
}

int main()
{
	//freopen("bzoj1515.in","r",stdin);
	//freopen("bzoj1515.out","w",stdout);
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		E[i]=Edge(u,v);
		deg[u]--;deg[v]++;
		id[E[i]]=i;
	}
	for(int i=1;i<=N;i++)
		if(deg[i]!=0)
			NIE();
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		int k;
		scanf("%d",&k);
		for(int j=1;j<=k;j++)
			scanf("%d",&v[j]);
		for(int j=1;j<k;j++)
		{
			if(id.count(Edge(v[j],v[j+1]))==0)
				NIE();
			v[j]=id[Edge(v[j],v[j+1])];
			if(vis[v[j]]==i)
				NIE();
			vis[v[j]]=i;
		}
		for(int j=1;j<k-1;j++)
		{
			if(!nxt[v[j]])
				nxt[v[j]]=v[j+1];
			else if(nxt[v[j]]!=v[j+1])
				NIE();
			if(!pre[v[j+1]])
				pre[v[j+1]]=v[j];
			else if(pre[v[j+1]]!=v[j])
				NIE();
		}
	}
	G.Clear();
	cnt=0;
	int p=0;
	memset(deg,0,sizeof deg);
	for(int i=1;i<=M;i++)
		if(pre[i]==0)
		{
			int j=i;
			while(j)
			{
				cnt++;
				if(nxt[j]==0)
					break;
				j=nxt[j];
			}
			G.AddEdge(E[i].first,E[j].second);
			p++;
			deg[E[j].second]++;deg[E[i].first]--;
		}
	if(cnt<M)
		NIE();
	for(int i=1;i<=N;i++)
		if(deg[i]!=0)
			NIE();
	cnt=0;
	Eular(1);
	for(int i=2;i<=N;i++)
		if(G.adj[i])
			NIE();
	//if(cnt<p)
	//	NIE();
	puts("TAK");
	
	return 0;
}
