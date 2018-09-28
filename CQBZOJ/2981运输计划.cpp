#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=300000;

int N,M;

struct Edge
{
    int v,t;
    Edge *nxt;
};
struct Path
{
    int u,v,len;
    bool operator < (const Path &t)const
    {return len<t.len;}
};

Edge E[MAXN*2],*adj[MAXN],*ecnt=E;

void AddEdge(int u,int v,int t)
{
    ecnt->v=v;ecnt->t=t;
    ecnt->nxt=adj[u];
    adj[u]=ecnt++;
    ecnt->v=u;ecnt->t=t;
    ecnt->nxt=adj[v];
    adj[v]=ecnt++;
}

int fa[MAXN],dis[MAXN],siz[MAXN],dep[MAXN];
int son[MAXN],tp[MAXN],id[MAXN],revid[MAXN],idc;

void GetSize(int u,int f=0,int deep=1)
{
    siz[u]=1;
    dep[u]=deep;
    for(Edge *p=adj[u];p;p=p->nxt)
    {
        int v=p->v;
        if(p->v!=f)
        {
            fa[v]=u;
            dis[v]=p->t;
            GetSize(v,u,deep+1);
            siz[u]+=siz[v];
        }
    }
}
void InitHeavyLightDecomposition(int u,int topp,int f=0)
{
    id[u]=++idc;
    revid[idc]=u;
    tp[u]=topp;
    int mx=0;
    for(Edge *p=adj[u];p;p=p->nxt)
    {
        int v=p->v;
        if(v!=f)
        {
            if(siz[v]>mx)
                mx=siz[v],son[u]=v;
        }
    }
    if(son[u])
        InitHeavyLightDecomposition(son[u],tp[u],u);
    for(Edge *p=adj[u];p;p=p->nxt)
    {
        int v=p->v;
        if(v!=f&&v!=son[u])
            InitHeavyLightDecomposition(v,v,u);
    }
}

int mnrk[MAXN*4],rk[MAXN*4];
int sum[MAXN];

void InitSum()
{
    for(int i=1;i<=N;i++)
        sum[i]=sum[i-1]+dis[revid[i]];
}
void Build(int L=1,int R=N,int id=1)
{
    mnrk[id]=rk[id]=M+1;
    if(L==R)
        return;
    int mid=(L+R)/2;
    Build(L,mid,id*2);
    Build(mid+1,R,id*2+1);
}
void Add(int l,int r,int val,int L=1,int R=N,int id=1)
{
    if(l<=L&&R<=r&&rk[id]!=M+2)
    {
        if(rk[id]==val+1)
            mnrk[id]=rk[id]=val;
        return;
    }
    int mid=(L+R)/2;

    if(rk[id]!=M+2)
        mnrk[id*2]=mnrk[id*2+1]=rk[id*2]=rk[id*2+1]=rk[id];

    if(l<=mid&&mnrk[id*2]<=val+1)
        Add(l,r,val,L,mid,id*2);
    if(mid<r&&mnrk[id*2+1]<=val+1)
        Add(l,r,val,mid+1,R,id*2+1);

    if(rk[id*2]==M+2||rk[id*2+1]==M+2||rk[id*2]!=rk[id*2+1])
        rk[id]=M+2;
    if(rk[id*2]==rk[id*2+1])
        rk[id]=rk[id*2];

    mnrk[id]=min(mnrk[id*2],mnrk[id*2+1]);
}
int Query(int pos,int L=1,int R=N,int id=1)
{
    if(rk[id]!=M+2||L==R)
        return rk[id];
    int mid=(L+R)/2;
    if(pos<=mid)
        return Query(pos,L,mid,id*2);
    return Query(pos,mid+1,R,id*2+1);
}

int PathLen(int u,int v)
{
    int ans=0;
    while(tp[u]!=tp[v])
    {
        if(dep[tp[u]]>dep[tp[v]])
            swap(u,v);
        //Add(id[tp[v]],id[v]);
        ans+=sum[id[v]]-sum[id[tp[v]]-1];
        v=fa[tp[v]];
    }
    if(dep[u]>dep[v])
        swap(u,v);
    if(u!=v)
    {
        //Add(id[u]+1,id[v]);
        ans+=sum[id[v]]-sum[id[u]];
    }
    return ans;
}
void PathAdd(int u,int v,int val)
{
    while(tp[u]!=tp[v])
    {
        if(dep[tp[u]]>dep[tp[v]])
            swap(u,v);
        Add(id[tp[v]],id[v],val);
        v=fa[tp[v]];
    }
    if(dep[u]>dep[v])
        swap(u,v);
    if(u!=v)
        Add(id[u]+1,id[v],val);
}

Path P[MAXN];

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<N;i++)
    {
        int u,v,t;
        scanf("%d%d%d",&u,&v,&t);
        AddEdge(u,v,t);
    }

    GetSize(1);
    idc=0;
    InitHeavyLightDecomposition(1,1);
    InitSum();

    for(int i=1;i<=M;i++)
    {
        scanf("%d%d",&P[i].u,&P[i].v);
        P[i].len=PathLen(P[i].u,P[i].v);
    }
    sort(P+1,P+M+1);
    Build();
    for(int i=M;i>0;i--)
        PathAdd(P[i].u,P[i].v,i);
    int ans=P[M].len;
    for(int i=2;i<=N;i++)
    {
        int pos=Query(id[i]);
        if(pos<=M)
            ans=min(ans,max(P[M].len-dis[i],P[pos-1].len));
    }
    printf("%d\n",ans);
    return 0;
}
