#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXM=300005,MAXLOG=20;

struct Edge
{
    int u,v,d;
    Edge(){}
    Edge(int _u,int _v,int _d)
    {u=_u;v=_v;d=_d;}

    bool operator < (const Edge &t)const
    {return d<t.d;}
};

struct DSU
{
    int fa[MAXN];
    void Clear()
    {memset(fa,0,sizeof fa);}
    int Root(int x)
    {
        if(fa[x]==0)
            return x;
        return fa[x]=Root(fa[x]);
    }
    void Union(int x,int y)
    {
        int r1=Root(x),r2=Root(y);
        if(r1!=r2)
            fa[r1]=r2;
    }
};

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

int N,M,K;
long long sum,ans;
Edge E[MAXM];
bool used[MAXM];
DSU linked;
Graph Tree;

void Kruskal_MakeTree()
{
    Tree.Clear();
    ans=0;
    sort(E+1,E+M+1);
    for(int i=1;i<=M;i++)
    {
        int r1=linked.Root(E[i].u),r2=linked.Root(E[i].v);
        if(r1==r2)
            continue;
        linked.Union(r1,r2);
        Tree.AddEdge(E[i].u,E[i].v,E[i].d);
        Tree.AddEdge(E[i].v,E[i].u,E[i].d);
        used[i]=true;
        sum+=E[i].d;
    }
}

int dep[MAXN],fa[MAXN][MAXLOG],mx[MAXN][MAXLOG],mx2[MAXN][MAXLOG];

void GetFirstTwo(int &res1,int &res2,int a=0,int b=0,int c=0,int d=0)
{
    int tmp[]={a,b,c,d};
    sort(tmp,tmp+4);
    res1=tmp[3];
    res2=0;
    for(int k=2;k>=0;k--)
        if(tmp[k]!=tmp[3])
        {
            res2=tmp[k];
            return;
        }
}

void dfs(int u)
{
    for(Graph::AdjEdge *e=Tree.adj[u];e;e=e->nxt)
    {
        int v=e->v;
        if(v==fa[u][0])
            continue;
        fa[v][0]=u;
        mx[v][0]=e->d;
        mx2[v][0]=0;
        dep[v]=dep[u]+1;
        dfs(v);
    }
}
void InitLCA()
{
    dfs(1);
    for(int j=1;j<MAXLOG;j++)
        for(int i=1;i<=N;i++)
            if(dep[i]-(1<<j)>=0)
            {
                fa[i][j]=fa[fa[i][j-1]][j-1];
                mx[i][j]=max(mx[i][j-1],mx[fa[i][j-1]][j-1]);
                GetFirstTwo(mx[i][j],mx2[i][j],mx[i][j-1],mx[fa[i][j-1]][j-1],mx2[i][j-1],mx2[fa[i][j-1]][j-1]);
            }
}
pair<int,int> FindPathMax(int u,int v)
{
    pair<int,int> res=make_pair(0,0);
    if(dep[u]>dep[v])
        swap(u,v);
    for(int j=MAXLOG-1;j>=0;j--)
        if(dep[v]-(1<<j)>=dep[u])
        {
            GetFirstTwo(res.first,res.second,res.first,res.second,mx[v][j],mx2[v][j]);
            v=fa[v][j];
        }
    if(u==v)
        return res;
    for(int j=MAXLOG-1;j>=0;j--)
        if(dep[u]-(1<<j)>=0&&fa[u][j]!=fa[v][j])
        {
            GetFirstTwo(res.first,res.second,res.first,res.second,mx[u][j],mx2[u][j]);
            GetFirstTwo(res.first,res.second,res.first,res.second,mx[v][j],mx2[v][j]);
            u=fa[u][j];
            v=fa[v][j];
        }
    GetFirstTwo(res.first,res.second,res.first,res.second,mx[u][0],mx2[u][0]);
    return res;
}

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;i++)
        scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].d);

    Kruskal_MakeTree();
    InitLCA();

    ans=0x3F3F3F3F3F3F3F3FLL;
    for(int i=1;i<=M;i++)
        if(!used[i])
        {
            pair<int,int> mx=FindPathMax(E[i].u,E[i].v);
            int delta=mx.first;
            if(delta==E[i].d)
                delta=mx.second;
            delta=-delta+E[i].d;
            ans=min(ans,sum+delta);
        }
    printf("%lld\n",ans);

    return 0;
}
