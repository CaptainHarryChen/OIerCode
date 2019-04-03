#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=250005,MAXLOG=20;

struct Edge
{
    int v,len;
    Edge(){}
    Edge(int a,int b):v(a),len(b){}
};

int n,h[MAXN];
vector<Edge> T[MAXN],VT[MAXN];
int fa[MAXN][MAXLOG],mn[MAXN][MAXLOG],lev[MAXN],dfn[MAXN],dfc;
bool flag[MAXN];

void AddEdge(vector<Edge> G[],int u,int v,int w)
{
    G[u].push_back(Edge(v,w));
    G[v].push_back(Edge(u,w));
}

void dfs(int u)
{
    dfn[u]=++dfc;
    for(int i=0;i<(int)T[u].size();i++)
    {
        int v=T[u][i].v;
        if(v==fa[u][0])
            continue;
        fa[v][0]=u;
        mn[v][0]=T[u][i].len;
        lev[v]=lev[u]+1;
        dfs(v);
    }
}
void Init()
{
    dfs(1);
    for(int j=1;j<MAXLOG;j++)
        for(int u=1;u<=n;u++)
            if(lev[u]-(1<<j)>=0)
            {
                fa[u][j]=fa[fa[u][j-1]][j-1];
                mn[u][j]=min(mn[u][j-1],mn[fa[u][j-1]][j-1]);
            }
}
int LCA(int u,int v)
{
    if(lev[u]>lev[v])
        swap(u,v);
    for(int j=MAXLOG-1;j>=0;j--)
        if(lev[v]-(1<<j)>=lev[u])
            v=fa[v][j];
    if(u==v)
        return u;
    for(int j=MAXLOG-1;j>=0;j--)
        if(lev[v]-(1<<j)>=0&&fa[u][j]!=fa[v][j])
            u=fa[u][j],v=fa[v][j];
    return fa[u][0];
}
int GetMin(int u,int v)
{
    if(lev[u]<lev[v])
        swap(u,v);
    int res=0x3F3F3F3F;
    for(int j=MAXLOG-1;j>=0;j--)
        if(lev[u]-(1<<j)>=lev[v])
        {
            res=min(res,mn[u][j]);
            u=fa[u][j];
        }
    return res;
}
long long DP(int u,int f=0,long long len=0x3F3F3F3F3F3F3F3FLL)
{
    long long res=len,tmp=0;
    for(int i=0;i<(int)VT[u].size();i++)
    {
        int v=VT[u][i].v;
        if(v==f)
            continue;
        tmp+=DP(v,u,VT[u][i].len);
    }
    if(!flag[u])
        res=min(res,tmp);
    VT[u].clear();
    return res;
}
bool dfncmp(int a,int b)
{return dfn[a]<dfn[b];}
void Solve(int m)
{
    static int stk[MAXN],tp;
    for(int i=1;i<=m;i++)
        flag[h[i]]=true;
    h[++m]=1;
    sort(h+1,h+m+1,dfncmp);
    tp=1;stk[1]=h[1];
    for(int i=2;i<=m;i++)
    {
        int l=LCA(h[i],stk[tp]);
        while(tp)
        {
            if(stk[tp]==l)
                break;
            if(tp==1||lev[stk[tp-1]]<lev[l])
            {
                AddEdge(VT,stk[tp],l,GetMin(stk[tp],l));
                tp--;
                stk[++tp]=l;
                break;
            }
            AddEdge(VT,stk[tp-1],stk[tp],GetMin(stk[tp-1],stk[tp]));
            tp--;
        }
        stk[++tp]=h[i];
    }
    while(tp>1)
    {
        AddEdge(VT,stk[tp-1],stk[tp],GetMin(stk[tp-1],stk[tp]));
        tp--;
    }
    printf("%lld\n",DP(1));
    for(int i=1;i<=m;i++)
        flag[h[i]]=false;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        AddEdge(T,u,v,w);
    }
    Init();
    int m;
    scanf("%d",&m);
    while(m--)
    {
        int k;
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d",&h[i]);
        Solve(k);
    }

    return 0;
}
