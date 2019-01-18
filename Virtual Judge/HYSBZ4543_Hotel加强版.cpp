#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005;

struct Edge
{
    int v;
    Edge *nxt;
};
struct Graph
{
    Edge edges[MAXN*2],*adj[MAXN],*edit;

    void Init()
    {
        memset(adj,0,sizeof adj);
        edit=edges;
    }
    void AddEdge(int u,int v)
    {
        edit->v=v;
        edit->nxt=adj[u];
        adj[u]=edit++;
    }
};

int n;
long long ans;
Graph Tr;

int len[MAXN],dep[MAXN],mxlen[MAXN],son[MAXN],fa[MAXN];
long long pool[MAXN*3],*pl_it;
long long *num[MAXN],*way[MAXN];

void PreDFS(int u)
{
    mxlen[u]=1;son[u]=0;
    for(Edge *e=Tr.adj[u];e;e=e->nxt)
    {
        int v=e->v;
        if(v==fa[u])
            continue;
        fa[v]=u;
        dep[v]=dep[u]+1;
        PreDFS(v);
        mxlen[u]=max(mxlen[u],mxlen[v]+1);
        if(mxlen[v]>mxlen[son[u]])
           son[u]=v;
    }
}

void dfs1(int u)
{
    num[u]=pl_it++;
    len[u]=1;
    if(son[u])
        dfs1(son[u]),len[u]+=len[son[u]];
    for(Edge *e=Tr.adj[u];e;e=e->nxt)
        if(e->v!=fa[u]&&e->v!=son[u])
            dfs1(e->v);
}
void dfs2(int u)
{
    for(Edge *e=Tr.adj[u];e;e=e->nxt)
        if(e->v!=fa[u]&&e->v!=son[u])
            dfs2(e->v),pl_it=way[e->v]+len[e->v];
    if(son[u])
        dfs2(son[u]);
    way[u]=pl_it++;
}

void Solve(int u)
{
    if(son[u])
        Solve(son[u]);
    num[u][0]=1;
    ans+=way[u][0];
    for(Edge *e=Tr.adj[u];e;e=e->nxt)
    {
        int v=e->v;
        if(v==fa[u]||v==son[u])
            continue;
        Solve(v);
        for(int d=0;d<len[v];d++)
        {
            ans+=way[u][d+1]*num[v][d];
            if(d-1>=0)
                ans+=way[v][d]*num[u][d-1];
        }
        for(int d=0;d<len[v];d++)
        {
            way[u][d+1]+=num[v][d]*num[u][d+1];
            if(d-1>=0)
                way[u][d-1]+=way[v][d];
            num[u][d+1]+=num[v][d];
        }
    }
}

int main()
{
    scanf("%d",&n);
    Tr.Init();
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        Tr.AddEdge(u,v);
        Tr.AddEdge(v,u);
    }
    PreDFS(1);
    ans=0;
    memset(pool,0,sizeof(long long)*n*3);
    pl_it=pool;
    dfs1(1);dfs2(1);
    Solve(1);
    printf("%lld\n",ans);
    return 0;
}
