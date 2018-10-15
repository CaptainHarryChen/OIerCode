#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=20005,MAXM=200005;

struct Edge
{
    int u,v,d;
    Edge(){}
    Edge(int _u,int _v,int _d)
    {u=_u;v=_v;d=_d;}

    bool operator < (const Edge &t)const
    {return d<t.d;}
};

struct Graph
{
    struct AdjEdge
    {
        int v,d;
        AdjEdge *nxt,*bck;
    }edges[MAXM*2],*adj[MAXN],*edges_it;

    void Clear()
    {
        memset(adj,0,sizeof adj);
        edges_it=edges;
    }
    void AddEdge(int u,int v,int d)
    {
        edges_it->v=v;
        edges_it->d=d;
        edges_it->nxt=adj[u];
        edges_it->bck=edges_it+1;
        adj[u]=edges_it++;
        edges_it->v=u;
        edges_it->d=d;
        edges_it->nxt=adj[v];
        edges_it->bck=edges_it-1;
        adj[v]=edges_it++;
    }
};

int N,M;
Edge E[MAXM];
Graph G;

int d[MAXN],cntd[MAXN];
int aug(int u,int augco,int S,int T)
{
    if(u==T)
        return augco;
    int augc=augco,mndis=N+1;
    for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
        if(e->d>0)
        {
            int v=e->v;
            if(d[v]==d[u]-1)
            {
                int delta=min(augc,e->d);
                delta=aug(v,delta,S,T);
                augc-=delta;
                e->d-=delta;
                e->bck->d+=delta;
                if(d[S]>N)
                    return augco-augc;
                if(augc==0)
                    break;
            }
            mndis=min(mndis,d[v]);
        }
    if(augc==augco)
    {
        cntd[d[u]]--;
        if(cntd[d[u]]==0)
        {
            d[S]=N+1;
            return 0;
        }
        d[u]=mndis+1;
        cntd[d[u]]++;
    }
    return augco-augc;
}

int ISAP(int S,int T)
{
    memset(d,0,sizeof d);
    memset(cntd,0,sizeof cntd);
    cntd[0]=N;
    int res=0;
    while(d[S]<N)
        res+=aug(S,0x3F3F3F3F,S,T);
    return res;
}

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;i++)
        scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].d);
    int U,V,L;
    scanf("%d%d%d",&U,&V,&L);

    int ans=0;
    G.Clear();
    for(int i=1;i<=M;i++)
        if(E[i].d<L)
            G.AddEdge(E[i].u,E[i].v,1);
    ans+=ISAP(U,V);
    G.Clear();
    for(int i=1;i<=M;i++)
        if(E[i].d>L)
            G.AddEdge(E[i].u,E[i].v,1);
    ans+=ISAP(U,V);
    printf("%d\n",ans);

    return 0;
}
