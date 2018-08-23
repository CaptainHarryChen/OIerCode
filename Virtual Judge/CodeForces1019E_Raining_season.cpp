#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=200005,MAXM=MAXN*3;

struct Edge
{
    int v,a,b,id;
    Edge()=default;
    Edge(int _v,int _a,int _b,int _id):v(_v),a(_a),b(_b),id(_id) {}
};

class Tree
{
public:
    int n;
    vector<Edge> adj[MAXN*2];

    vector<Edge> &operator [] (unsigned int i)
    {
        return adj[i];
    }
    void AddEdge(int u,int v,int a,int b,int i)
    {
        adj[u].emplace_back(v,a,b,i);
        adj[v].emplace_back(u,a,b,i);
    }
};

struct Path
{
    long long a,b;
    Path()=default;
    Path(long long _a,long long _b):a(_a),b(_b) {}
    bool operator < (const Path &t)const
    {
        return a<t.a||(a==t.a&&b<t.b);
    }
};

int N,M,edgeid;
Tree F,G;

void ToBinaryTree(int u,int fa=0)
{
    int last=u;
    for(const auto &e:F[u])
        if(e.v!=fa)
        {
            G.AddEdge(last,++G.n,0,0,++edgeid);
            G.AddEdge(G.n,e.v,e.a,e.b,++edgeid);
            last=G.n;
            ToBinaryTree(e.v,u);
        }
}

bool disable[MAXM];
int siz[MAXN];
Edge E[MAXN];
void GetSize(int u,int fa=0)
{
    siz[u]=1;
    for(const auto &e:G[u])
        if(e.v!=fa&&!disable[e.id])
        {
            E[e.v]=Edge(u,e.a,e.b,e.id);
            GetSize(e.v,u);
            siz[u]+=siz[e.v];
        }
}
int FindCentroid(int u,int lim,int fa=0)
{
    if(siz[u]<=lim)
        return u;
    int mxsiz=0,id;
    for(const auto &e:G[u])
        if(e.v!=fa&&!disable[e.id])
        {
            int tmp=FindCentroid(e.v,lim,u);
            if(siz[tmp]>mxsiz)
                mxsiz=siz[tmp],id=tmp;
        }
    return id;
}

void GetPath(int u,vector<Path> &P,Path now=Path(0,0),int fa=0)
{
    if(G[u].size()==1)
        P.push_back(now);
    for(const auto &e:G[u])
        if(e.v!=fa&&!disable[e.id])
            GetPath(e.v,P,Path(now.a+e.a,now.b+e.b),u);
}

void Process(vector<Path> &P)
{
    static vector<Path> tmp;
    sort(P.begin(),P.end());
    tmp.resize(P.size());
    tmp.emplace_back(0,0);
    int top=0;
    for(const auto &p:P)
    {
        while(top>0&&(p.a==tmp[top].a&&p.b>=tmp[top].b))
              top--;
        if(p.a==tmp[top].a&&p.b<=tmp[top].b)
            continue;
        while(top>0&&1.0*(tmp[top].b-tmp[top-1].b)/(tmp[top].a-tmp[top-1].a)<1.0*(p.b-tmp[top].b)/(p.a-tmp[top].a))
            top--;
        tmp[++top]=p;
    }
    for(int i=0; i<=top; i++)
        P[i]=tmp[i];
    P.resize(top+1);
}

vector<Path> P1,P2,P;

void CentroidDecomposition(int u)
{
    GetSize(u);
    if(siz[u]<=1)
        return;
    int centroid1=FindCentroid(u,siz[u]/2);
    int centroid2=E[centroid1].v;

    disable[E[centroid1].id]=true;
    P1.clear();
    P2.clear();
    P1.emplace_back(0,0);
    P2.emplace_back(0,0);
    GetPath(centroid1,P1);
    GetPath(centroid2,P2);

    Process(P1);
    Process(P2);

    int x=0,y=0;
    while(x<(int)P1.size()&&y<(int)P2.size())
    {
        P.emplace_back(P1[x].a+P2[y].a+E[centroid1].a,P1[x].b+P2[y].b+E[centroid1].b);
        double k1=-1e100,k2=-1e100;
        if(x<(int)P1.size()-1)
            k1=1.0*(P1[x+1].b-P1[x].b)/(P1[x+1].a-P1[x].a);
        if(y<(int)P2.size()-1)
            k2=1.0*(P2[y+1].b-P2[y].b)/(P2[y+1].a-P2[y].a);
        if(k1>k2)
            x++;
        else
            y++;
    }

    CentroidDecomposition(centroid1);
    CentroidDecomposition(centroid2);
}

int main()
{
    scanf("%d%d",&N,&M);
    F.n=N;
    for(int i=1; i<N; i++)
    {
        int u,v,a,b;
        scanf("%d%d%d%d",&u,&v,&a,&b);
        F.AddEdge(u,v,a,b,i);
    }

    G.n=N;
    ToBinaryTree(1);

    P.emplace_back(0,0);
    CentroidDecomposition(1);
    Process(P);

    int id=0;
    for(int t=0; t<M; t++)
    {
        while(id<(int)P.size()-1&&(1LL*t*P[id+1].a+P[id+1].b)>(1LL*t*P[id].a+P[id].b))
            id++;
        long long ans=1LL*t*P[id].a+P[id].b;
        printf("%I64d ",ans);
    }
    puts("");

    return 0;
}
