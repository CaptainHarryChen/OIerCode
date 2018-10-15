#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=30005,MAXM=60005;

struct Graph
{
    struct AdjEdge
    {
        int v,d;
        AdjEdge *nxt;
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
        adj[u]=edges_it++;
    }
};

int n,m,K;
Graph G;

int dis[MAXN];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > Q;

void Dijkstra(int s)
{
    memset(dis,0x3F,sizeof dis);
    dis[s]=0;
    Q.push(make_pair(0,s));
    while(!Q.empty())
    {
        pair<int,int> st=Q.top();
        Q.pop();
        int u=st.second;
        if(dis[u]<st.first)
            continue;
        for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
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

Graph Tree;

void MakeTree()
{
    static int fa[MAXN],d[MAXN];
    Tree.Clear();
    memset(fa,0x3F,sizeof fa);
    for(int u=1;u<=n;u++)
        for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
            if(dis[u]+e->d==dis[e->v])
            {
                int v=e->v;
                fa[v]=min(fa[v],u);
                d[v]=e->d;
            }
    for(int i=2;i<=n;i++)
    {
        Tree.AddEdge(fa[i],i,d[i]);
        Tree.AddEdge(i,fa[i],d[i]);
    }
}

int dep[MAXN];
bool vis[MAXN];

int mxlen[MAXN],cnt[MAXN],ti[MAXN];

int val[MAXN],siz[MAXN];
int stk[MAXN],tp;
void dfs(int u,int fa=0)
{
    siz[u]=1;
    val[u]=0;
    stk[++tp]=u;
    for(Graph::AdjEdge *e=Tree.adj[u];e;e=e->nxt)
    {
        int v=e->v;
        if(v==fa||vis[v])
            continue;
        dfs(v,u);
        siz[u]+=siz[v];
        val[u]=max(val[u],siz[v]);
    }
}
int FindCentroid(int s)
{
    tp=0;
    dfs(s);
    int best=0x3F3F3F3F,mxid;
    for(int i=1;i<=tp;i++)
    {
        int u=stk[i];
        val[u]=max(val[u],siz[s]-siz[u]);
        if(best>val[u])
        {
            best=val[u];
            mxid=u;
        }
    }
    return mxid;
}

int anslen;
long long anscnt;

void UpdateAns(int s,int u,int fa,int dep,int len)
{
    if(dep>K)
        return;
    if(ti[K-dep]!=s)
        ti[K-dep]=s,mxlen[K-dep]=cnt[K-dep]=0;
    if(cnt[K-dep])
    {
        if(anslen==mxlen[K-dep]+len)
            anscnt+=cnt[K-dep];
        if(anslen<mxlen[K-dep]+len)
            anslen=mxlen[K-dep]+len,anscnt=cnt[K-dep];
    }
    for(Graph::AdjEdge *e=Tree.adj[u];e;e=e->nxt)
    {
        int v=e->v;
        if(v==fa||vis[v])
            continue;
        UpdateAns(s,v,u,dep+1,len+e->d);
    }
}
void UpdateState(int s,int u,int fa,int dep,int len)
{
    if(dep>K-1)
        return;
    if(ti[dep]!=s)
        ti[dep]=s,mxlen[dep]=cnt[dep]=0;
    if(mxlen[dep]==len)
        cnt[dep]++;
    if(mxlen[dep]<len)
        mxlen[dep]=len,cnt[dep]=1;
    for(Graph::AdjEdge *e=Tree.adj[u];e;e=e->nxt)
    {
        int v=e->v;
        if(v==fa||vis[v])
            continue;
        UpdateState(s,v,u,dep+1,len+e->d);
    }
}

void CentroidDecomposition(int s)
{
    int g=FindCentroid(s);
    ti[0]=g;
    mxlen[0]=0;cnt[0]=1;
    for(Graph::AdjEdge *e=Tree.adj[g];e;e=e->nxt)
    {
        int v=e->v;
        if(vis[v])
            continue;
        UpdateAns(g,v,g,2,e->d);
        UpdateState(g,v,g,1,e->d);
    }
    vis[g]=true;
    for(Graph::AdjEdge *e=Tree.adj[g];e;e=e->nxt)
    {
        int v=e->v;
        if(vis[v])
            continue;
        CentroidDecomposition(v);
    }
}

int main()
{
    scanf("%d%d%d",&n,&m,&K);
    G.Clear();
    for(int i=1;i<=m;i++)
    {
        int A,B,C;
        scanf("%d%d%d",&A,&B,&C);
        G.AddEdge(A,B,C);
        G.AddEdge(B,A,C);
    }

    Dijkstra(1);
    MakeTree();

    CentroidDecomposition(1);

    printf("%d %lld\n",anslen,anscnt);

    return 0;
}
