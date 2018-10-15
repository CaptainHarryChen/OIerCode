#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=1505,MAXM=5005,MOD=1000000007;

struct Graph
{
    struct AdjEdge
    {
        int v,d,id;
        AdjEdge *nxt;
    }edges[MAXM*2],*adj[MAXN],*edges_it;

    void Clear()
    {
        memset(adj,0,sizeof adj);
        edges_it=edges;
    }
    void AddEdge(int u,int v,int d,int id)
    {
        edges_it->v=v;
        edges_it->d=d;
        edges_it->id=id;
        edges_it->nxt=adj[u];
        adj[u]=edges_it++;
    }
};

struct Edge
{
    int u,v,d;
    Edge(){}
    Edge(int _u,int _v,int _d)
    {u=_u;v=_v;d=_d;}
};

int n,m;
Graph G;
Edge edges[MAXM];

queue<int> Q;
int dis[MAXN];
bool inq[MAXN];

void SPFA(int s)
{
    memset(dis,0x3F,sizeof dis);
    memset(inq,0,sizeof inq);
    Q.push(s);
    dis[s]=0;
    inq[s]=true;
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        inq[u]=false;
        for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
        {
            int v=e->v;
            if(dis[v]>dis[u]+e->d)
            {
                dis[v]=dis[u]+e->d;
                if(!inq[v])
                {
                    inq[v]=true;
                    Q.push(v);
                }
            }
        }
    }
}

bool vis[MAXN];
int deg[MAXN],cntin[MAXN],cntout[MAXN];

void CalcDegree(int u)
{
    vis[u]=true;
    for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
        if(dis[u]+e->d==dis[e->v])
        {
            int v=e->v;
            deg[v]++;
            if(!vis[v])
                CalcDegree(v);
        }
}
void Calc_cntin(int u)
{
    for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
        if(dis[u]+e->d==dis[e->v])
        {
            int v=e->v;
            cntin[v]+=cntin[u];
            deg[v]--;
            if(deg[v]==0)
                Calc_cntin(v);
        }
}
void Calc_cntout(int u)
{
    cntout[u]=1;
    for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
        if(dis[u]+e->d==dis[e->v])
        {
            int v=e->v;
            if(cntout[v]==0)
                Calc_cntout(v);
            cntout[u]+=cntout[v];
        }
}

long long ans[MAXM];

int main()
{
    scanf("%d%d",&n,&m);
    G.Clear();
    for(int i=1;i<=m;i++)
    {
        int u,v,d;
        scanf("%d%d%d",&u,&v,&d);
        edges[i]=Edge(u,v,d);
        G.AddEdge(u,v,d,i);
    }

    for(int s=1;s<=n;s++)
    {
        SPFA(s);

        memset(vis,0,sizeof vis);
        memset(deg,0,sizeof deg);
        CalcDegree(s);

        memset(cntin,0,sizeof cntin);
        cntin[s]=1;
        Calc_cntin(s);

        memset(cntout,0,sizeof cntout);
        Calc_cntout(s);

        for(int i=1;i<=m;i++)
            if(dis[edges[i].u]+edges[i].d==dis[edges[i].v])
                ans[i]=(ans[i]+1LL*cntin[edges[i].u]*cntout[edges[i].v]%MOD)%MOD;
    }

    for(int i=1;i<=m;i++)
        printf("%lld\n",ans[i]);

    return 0;
}
