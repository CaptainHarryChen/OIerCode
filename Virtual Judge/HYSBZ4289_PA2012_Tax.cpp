#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=400010,MAXM=1600010;

template<class T>
void Read(T &x)
{
	char c;
	bool f=0;
	while(c=getchar(),c!=EOF)
	{
		if(c=='-')
			f=1;
		else if(c>='0'&&c<='9')
		{
			x=c-'0';
			while(c=getchar(),c>='0'&&c<='9')
				x=x*10+c-'0';
			if(f)
				x=-x;
			return;
		}
	}
}

struct Graph
{
    struct AdjEdge
    {
        int v,d,id;
        AdjEdge *nxt;
    }edges[MAXM],*adj[MAXN],*edges_it;

    void Clear()
    {
        memset(adj,0,sizeof adj);
        edges_it=edges;
    }
    void AddEdge(int u,int v,int d,int i=0)
    {
        edges_it->v=v;
        edges_it->d=d;
        edges_it->id=i;
        edges_it->nxt=adj[u];
        adj[u]=edges_it++;
    }
};

struct Edge
{
    int u,v,d,id;
    Edge(){}
    Edge(int _u,int _v,int _d,int _id=0)
    {u=_u;v=_v;d=_d;id=_id;}
    bool operator < (const Edge &t)const
    {return d<t.d;}
};

int n,m;
Graph G,F;
Edge edges[MAXM];

priority_queue<pair<long long,int>,vector<pair<long long,int> >,greater<pair<long long,int> > > Q;
long long dis[MAXN];

void SPFA()
{
    memset(dis,0x3F,sizeof dis);
    for(Graph::AdjEdge *e=G.adj[1];e;e=e->nxt)
    {
        dis[e->id]=e->d;
        Q.push(make_pair(e->d,e->id));
    }
    while(!Q.empty())
    {
        pair<int,int> tmp=Q.top();
        Q.pop();
        int u=tmp.second;
        if(dis[u]<tmp.first)
            continue;
        for(Graph::AdjEdge *e=F.adj[u];e;e=e->nxt)
        {
            int v=e->v;
            if(dis[v]>dis[u]+e->d)
            {
                dis[v]=dis[u]+e->d;
                Q.push(make_pair(dis[v],v));
            }
        }
    }
}

int tp;
Edge tmp[MAXN];

int main()
{
    Read(n);Read(m);
    G.Clear();
    F.Clear();
    int it=0;
    //edges[++it]=Edge(0,1,0);
    for(int i=1;i<=m;i++)
    {
        int u,v,d;
        Read(u);Read(v);Read(d);
        edges[++it]=Edge(u,v,d);
        edges[++it]=Edge(v,u,d);
        G.AddEdge(u,v,d,it-1);
        G.AddEdge(v,u,d,it);
    }
    for(int i=1;i<=n;i++)
    {
        tp=0;
        for(Graph::AdjEdge *e=G.adj[i];e;e=e->nxt)
            tmp[++tp]=Edge(i,e->v,e->d,e->id);
        if(tp==0)
            continue;
        sort(tmp+1,tmp+tp+1);
        for(int i=1;i<tp;i++)
        {
            F.AddEdge(tmp[i].id,tmp[i+1].id,tmp[i+1].d-tmp[i].d);
            F.AddEdge(tmp[i+1].id,tmp[i].id,0);
        }
        for(int i=1;i<=tp;i++)
            F.AddEdge(tmp[i].id,((tmp[i].id-1)^1)+1,tmp[i].d);
    }
    //edges[++it]=Edge(n,n+1,0);
    //G.AddEdge(n,n+1,0,it);

    SPFA();

    long long ans=0x3F3F3F3F3F3F3F3FLL;
    for(Graph::AdjEdge *e=G.adj[n];e;e=e->nxt)
        ans=min(ans,dis[((e->id-1)^1)+1]+e->d);
    printf("%lld\n",ans);

    return 0;
}
