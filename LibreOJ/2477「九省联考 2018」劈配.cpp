#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=205;

namespace ISAP
{
    const int MAXNODE=410,MAXEDGE=80000,INF=0x3F3F3F3F;

    struct Edge
    {
        int v,c;
        Edge *nxt,*bck;
    }edges[MAXEDGE],*adj[MAXNODE],*ecnt=edges;
    void AddEdge(int u,int v,int c)
    {
        ecnt->v=v;ecnt->c=c;
        ecnt->nxt=adj[u];
        ecnt->bck=ecnt+1;
        adj[u]=ecnt++;
        ecnt->v=u;ecnt->c=0;
        ecnt->nxt=adj[v];
        ecnt->bck=ecnt-1;
        adj[v]=ecnt++;
    }
    void DelEdge(int u)
    {
        int cnt=0;
        Edge *e=adj[u];
        while(e->nxt)
        {
            adj[e->v]=adj[e->v]->nxt;
            e=e->nxt,cnt++;
        }
        adj[u]=e;
    }
    void Init()
    {
        memset(adj,0,sizeof adj);
        ecnt=edges;
    }

    int d[MAXNODE],cntd[MAXNODE];

    int aug(int u,int augco,int S,int T,int n)
    {
        if(u==T)
            return augco;
        int best=n,delta,augc=augco;
        for(Edge *p=adj[u];p;p=p->nxt)
        {
            int v=p->v;
            if(p->c>0&&d[v]==d[u]-1)
            {
                delta=min(p->c,augc);
                delta=aug(v,delta,S,T,n);
                p->c-=delta;
                p->bck->c+=delta;
                augc-=delta;
                if(d[S]==n)
                    return augco-augc;
                if(augc==0)
                    break;
            }
            if(p->c>0)
                best=min(best,d[v]);
        }
        if(augc==augco)
        {
            cntd[d[u]]--;
            if(cntd[d[u]]==0)
            {d[S]=n;return 0;}
            d[u]=best+1;
            cntd[d[u]]++;
        }
        return augco-augc;
    }
    int Solve(int S,int T,int n)
    {
        int flow=0;
        memset(d,0,sizeof d);
        memset(cntd,0,sizeof cntd);
        cntd[0]=n;
        while(d[S]<n)
            flow+=aug(S,INF,S,T,n);
        return flow;
    }
}

int T,C,n,m,b[MAXN],s[MAXN],ans[MAXN];
vector<int> a[MAXN][MAXN];

void Init()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            a[i][j].clear();
}
void Solve1()
{
    ISAP::Init();
    for(int i=1;i<=n;i++)
        ISAP::AddEdge(0,i,1);
    for(int i=1;i<=m;i++)
        ISAP::AddEdge(n+i,n+m+1,b[i]);
    for(int i=1;i<=n;i++)
    {
        ans[i]=m+1;
        for(int j=1;j<=m;j++)
        {
            for(int k=0;k<(int)a[i][j].size();k++)
                ISAP::AddEdge(i,a[i][j][k]+n,1);
            if(ISAP::Solve(0,n+m+1,n+m+2))
            {
                ans[i]=j;
                break;
            }
            ISAP::DelEdge(i);
        }
    }
    for(int i=1;i<=n;i++)
        printf("%d%c",ans[i]," \n"[i==n]);
}
int Calc(int prev,int now)
{
    ISAP::Init();
    for(int i=1;i<=n;i++)
        ISAP::AddEdge(0,i,1);
    for(int i=1;i<=m;i++)
        ISAP::AddEdge(n+i,n+m+1,b[i]);
    for(int i=1;i<=prev;i++)
        if(ans[i]<=m)
            for(int k=0;k<(int)a[i][ans[i]].size();k++)
                ISAP::AddEdge(i,a[i][ans[i]][k]+n,1);
    ISAP::Solve(0,n+m+1,n+m+2);
    int res=m+1;
    for(int j=1;j<=m;j++)
    {
        for(int k=0;k<(int)a[now][j].size();k++)
            ISAP::AddEdge(now,a[now][j][k]+n,1);
        if(ISAP::Solve(0,n+m+1,n+m+2))
        {
            res=j;
            break;
        }
        ISAP::DelEdge(now);
    }
    return res;
}
void Solve2()
{
    for(int i=1;i<=n;i++)
    {
        int L=0,R=i-1,res=i;
        while(L<=R)
        {
            int mid=(L+R)/2;
            if(Calc(i-mid-1,i)<=s[i])
                res=mid,R=mid-1;
            else
                L=mid+1;
        }
        printf("%d%c",res," \n"[i==n]);
    }
}

int main()
{
    scanf("%d%d",&T,&C);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        Init();
        for(int i=1;i<=m;i++)
            scanf("%d",&b[i]);
        for(int i=1;i<=n;i++)
            for(int j=1,x;j<=m;j++)
            {
                scanf("%d",&x);
                if(x)
                    a[i][x].push_back(j);
            }
        for(int i=1;i<=n;i++)
            scanf("%d",&s[i]);
        Solve1();
        Solve2();
    }
    return 0;
}
