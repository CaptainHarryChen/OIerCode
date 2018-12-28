#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=10005,INF=0x3F3F3F3F;

int M,N,Q,nodecnt;

namespace ISAP
{
    const int MAX_NODE=MAXN*16,MAX_EDGE=MAXN*200;
    struct Edge
    {
        int v,cap;
        Edge *nxt,*bck;
        Edge(){}
        Edge(int _v,int _c,Edge *n,Edge *b)
        {v=_v;cap=_c;nxt=n;bck=b;}
    }edges[MAX_EDGE*2],*adj[MAX_NODE],*ed_it=edges;

    void AddEdge(int u,int v,int c)
    {
        //fprintf(stderr,"AddEdge(%2d %2d %14d)\n",u,v,c);
        *ed_it=Edge(v,c,adj[u],ed_it+1);
        adj[u]=ed_it;
        ed_it++;
        *ed_it=Edge(u,0,adj[v],ed_it-1);
        adj[v]=ed_it;
        ed_it++;
    }

    int d[MAX_NODE],cntd[MAX_NODE];

    int aug(int u,int augco,int S,int T,int N)
    {
        if(u==T)
            return augco;
        int augc=augco,delta,mindep=N;
        for(Edge *e=adj[u];e;e=e->nxt)
        {
            int v=e->v;
            if(e->cap>0)
            {
                if(d[v]==d[u]-1)
                {
                    delta=min(augc,e->cap);
                    delta=aug(v,delta,S,T,N);
                    e->cap-=delta;
                    e->bck->cap+=delta;
                    augc-=delta;
                    if(d[S]>=N)
                        return augco-augc;
                    if(augc==0)
                        break;
                }
                mindep=min(mindep,d[v]);
            }
        }
        if(augco==augc)
        {
            cntd[d[u]]--;
            if(cntd[d[u]]==0)
            {
                d[S]=N;
                return 0;
            }
            d[u]=mindep+1;
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
}

namespace SegmentTree
{
    struct Node
    {
        int x;
        Node *son[2];
    }nodes[MAXN*8],*nd_it=nodes+1;
    int ID(Node *u)
    {return u-nodes;}

    void Build(Node *&u,int dir,int L=1,int R=N)
    {
        if(u==NULL)
            u=nd_it++;
        if(L==R)
            return;
        int mid=(L+R)/2;
        Build(u->son[0],dir,L,mid);
        Build(u->son[1],dir,mid+1,R);
        if(dir==1)
        {
            ISAP::AddEdge(ID(u),ID(u->son[0]),INF);
            ISAP::AddEdge(ID(u),ID(u->son[1]),INF);
        }
        else
        {
            ISAP::AddEdge(ID(u->son[0]),ID(u),INF);
            ISAP::AddEdge(ID(u->son[1]),ID(u),INF);
        }
    }
    void BuildST(Node *u,int v,int dir,int L=1,int R=N)
    {
        if(L==R)
        {
            if(dir==-1)
                ISAP::AddEdge(v,ID(u),1);
            else
                ISAP::AddEdge(ID(u),v,1);
            return;
        }
        int mid=(L+R)/2;
        BuildST(u->son[0],v,dir,L,mid);
        BuildST(u->son[1],v,dir,mid+1,R);
    }
    void Update(Node *u,int l,int r,int v,int dir,int L=1,int R=N)
    {
        if(l<=L&&R<=r)
        {
            if(dir==1)
                ISAP::AddEdge(ID(u),v,INF);
            else
                ISAP::AddEdge(v,ID(u),INF);
            return;
        }
        int mid=(L+R)/2;
        if(l<=mid)
            Update(u->son[0],l,r,v,dir,L,mid);
        if(mid<r)
            Update(u->son[1],l,r,v,dir,mid+1,R);
    }
}

struct Seg
{
    int x,l,r;
    bool type;
    Seg(){}
    Seg(int x,int l,int r,bool t):x(x),l(l),r(r),type(t){}
    bool operator < (const Seg &s)const
    {return x<s.x||(x==s.x&&type<s.type);}
};

Seg side[MAXN*2];
SegmentTree::Node *r1,*r2;

namespace Scanner
{
    int h[MAXN];

    void Insert(int l,int r,int x)
    {
        for(int i=l;i<=r;i++)
            h[i]=x;
    }
    void Update(int l,int r,int x)
    {
        int last=l;
        for(int i=l;i<=r+1;i++)
            if(h[i]!=h[last]||i==r+1)
            {
                if(h[last]<x)
                {
                    nodecnt++;
                    SegmentTree::Update(r2,h[last]+1,x,nodecnt,1);
                    SegmentTree::Update(r1,last,i-1,nodecnt,-1);
                }
                last=i;
            }
        for(int i=l;i<=r;i++)
            h[i]=-1;
    }
}

int main()
{
    scanf("%d%d",&N,&Q);
    for(int i=1;i<=Q;i++)
    {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        side[++M]=Seg(x1-1,y1,y2,1);
        side[++M]=Seg(x2,y1,y2,0);
    }
    sort(side+1,side+M+1);

    SegmentTree::Build(r1,1);
    SegmentTree::Build(r2,-1);
    nodecnt=SegmentTree::ID(SegmentTree::nd_it);

    for(int i=1;i<=M;i++)
    {
        if(side[i].type==0)
            Scanner::Insert(side[i].l,side[i].r,side[i].x);
        else
            Scanner::Update(side[i].l,side[i].r,side[i].x);
    }
    Scanner::Update(1,N,N);

    int S=++nodecnt,T=++nodecnt;
    SegmentTree::BuildST(r2,S,-1);
    SegmentTree::BuildST(r1,T,1);

    int ans=ISAP::Solve(S,T,nodecnt);
    printf("%d\n",ans);

    return 0;
}
