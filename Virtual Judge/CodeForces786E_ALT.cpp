#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=20005;

int N,M;
vector<int> ans1,ans2;

namespace ISAP
{
    const int INF=0x3F3F3F3F,MAX_NODE=MAXN*3,MAX_EDGE=MAXN*40;
    int idd[MAX_NODE];
    struct Edge
    {
        int v,cap;
        Edge *bck,*nxt;
        Edge(){}
        Edge(int v,int cap,Edge *bck,Edge *nxt):v(v),cap(cap),bck(bck),nxt(nxt){}
    }edges[MAX_EDGE*2],*adj[MAX_NODE],*ed_it=edges;

    void AddEdge(int u,int v,int c)
    {
        //printf("(%2d %2d %10d)\n",u,v,c);
        *ed_it=Edge(v,c,ed_it+1,adj[u]);
        adj[u]=ed_it++;
        *ed_it=Edge(u,0,ed_it-1,adj[v]);
        adj[v]=ed_it++;
    }

    int d[MAX_NODE],cntd[MAX_NODE];
    int aug(int u,int augco,int S,int T,int N)
    {
        if(u==T)
            return augco;
        int augc=augco,mndis=N;
        for(Edge *e=adj[u];e;e=e->nxt)
            if(e->cap>0)
            {
                if(d[e->v]==d[u]-1)
                {
                    int delta=min(e->cap,augc);
                    delta=aug(e->v,delta,S,T,N);
                    e->cap-=delta;
                    e->bck->cap+=delta;
                    augc-=delta;
                    if(d[S]>=N)
                        return augco-augc;
                    if(augc==0)
                        break;
                }
                mndis=min(mndis,d[e->v]);
            }
        if(augco==augc)
        {
            cntd[d[u]]--;
            if(cntd[d[u]]==0)
            {
                d[S]=N;
                return 0;
            }
            d[u]=mndis+1;
            cntd[d[u]]++;
        }
        return augco-augc;
    }
    int Solve(int S,int T,int N)
    {
        memset(d,0,sizeof d);
        memset(cntd,0,sizeof cntd);
        cntd[0]=N;
        int flow=0;
        while(d[S]<N)
            flow+=aug(S,INF,S,T,N);
        return flow;
    }
    bool vis[MAX_NODE];
    void Mark(int u)
    {
        vis[u]=true;
        for(Edge *e=adj[u];e;e=e->nxt)
            if(e->cap>0&&!vis[e->v])
                Mark(e->v);
    }
    void GetAns(int S,int T,int N)
    {
        Mark(S);
        for(int i=1;i<=N;i++)
            for(Edge *e=adj[i];e;e=e->nxt)
                if(vis[i]&&!vis[e->v])
                {
                    if(i==S)
                        ans1.push_back(idd[e->v]);
                    if(e->v==T)
                        ans2.push_back(idd[i]);
                }
    }
}

namespace HLD
{
    int eeid[MAXN],rid[MAXN];
    struct Node
    {Node *son[2];}nodes[MAXN*2],*nd_it=nodes;
    int ID(Node *u)
    {return u-nodes+1;}

    void BuildSegmentTree(Node *&u,int L=1,int R=N)
    {
        if(u==NULL)
            u=nd_it++;
        if(L==R)
            return;
        int mid=(L+R)/2;
        BuildSegmentTree(u->son[0],L,mid);
        BuildSegmentTree(u->son[1],mid+1,R);
        ISAP::AddEdge(ID(u),ID(u->son[0]),0x3F3F3F3F);
        ISAP::AddEdge(ID(u),ID(u->son[1]),0x3F3F3F3F);
    }
    void BuildEdge(Node *u,int t,int L=1,int R=N)
    {
        if(L==R)
        {
            if(L!=1)
            {
                ISAP::idd[ID(u)]=eeid[rid[L]];
                ISAP::AddEdge(ID(u),t,1);
            }
            return;
        }
        int mid=(L+R)/2;
        BuildEdge(u->son[0],t,L,mid);
        BuildEdge(u->son[1],t,mid+1,R);
    }
    void AddSegEdge(Node *u,int l,int r,int i,int L=1,int R=N)
    {
        if(l<=L&&R<=r)
        {
            ISAP::AddEdge(i,ID(u),0x3F3F3F3F);
            return;
        }
        int mid=(L+R)/2;
        if(l<=mid)
            AddSegEdge(u->son[0],l,r,i,L,mid);
        if(mid<r)
            AddSegEdge(u->son[1],l,r,i,mid+1,R);
    }

    vector<int> adj[MAXN],eid[MAXN];
    void AddEdge(int u,int v,int i)
    {
        adj[u].push_back(v);
        eid[u].push_back(i);
        adj[v].push_back(u);
        eid[v].push_back(i);
    }

    int fa[MAXN],dep[MAXN],siz[MAXN],son[MAXN],tp[MAXN],id[MAXN],idc;

    void dfs1(int u)
    {
        siz[u]=1;
        for(int i=0;i<(int)adj[u].size();i++)
        {
            int v=adj[u][i];
            if(v!=fa[u])
            {
                fa[v]=u;
                dep[v]=dep[u]+1;
                eeid[v]=eid[u][i];
                dfs1(v);
                siz[u]+=siz[v];
            }
        }
    }
    void dfs2(int u,int t)
    {
        id[u]=++idc;
        rid[idc]=u;
        tp[u]=t;
        for(auto v:adj[u])
            if(v!=fa[u])
                if(siz[v]>siz[son[u]])
                    son[u]=v;
        if(son[u])
            dfs2(son[u],t);
        for(auto v:adj[u])
            if(v!=son[u]&&v!=fa[u])
                dfs2(v,v);
    }
    void Init()
    {dfs1(1);dfs2(1,1);}
}

HLD::Node *rt;

void MakeNet(int i,int x,int y)
{
    using namespace HLD;
    while(tp[x]!=tp[y])
    {
        if(dep[tp[x]]>dep[tp[y]])
            swap(x,y);
        AddSegEdge(rt,id[tp[y]],id[y],i);
        y=fa[tp[y]];
    }
    if(x==y)
        return;
    if(dep[x]>dep[y])
        swap(x,y);
    AddSegEdge(rt,id[x]+1,id[y],i);
}

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<N;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        HLD::AddEdge(u,v,i);
    }

    HLD::Init();
    HLD::BuildSegmentTree(rt);

    int used=HLD::ID(HLD::nd_it);
    int S=used+M,T=S+1;
    HLD::BuildEdge(rt,T);

    for(int i=1;i<=M;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        ISAP::idd[used+i-1]=i;
        ISAP::AddEdge(S,used+i-1,1);
        MakeNet(used+i-1,x,y);
    }

    int ans=ISAP::Solve(S,T,T);
    printf("%d\n",ans);
    ISAP::GetAns(S,T,T);
    printf("%d",(int)ans1.size());
    for(int i=0;i<(int)ans1.size();i++)
        printf(" %d",ans1[i]);
    printf("\n%d",(int)ans2.size());
    for(int i=0;i<(int)ans2.size();i++)
        printf(" %d",ans2[i]);
    puts("");

    return 0;
}
