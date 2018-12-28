#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=250005,MAXLOG=20;

struct Edge
{
    int v,l;
    Edge(){}
    Edge(int v,int l):v(v),l(l){}
};

int n,m;
vector<Edge> adj[MAXN];

int vfa[MAXN];
vector<int> vson[MAXN];

int lev[MAXN],dfn[MAXN],dfc;
int fa[MAXN][MAXLOG],mn[MAXN][MAXLOG];

void dfs(int u)
{
    dfn[u]=++dfc;
    for(int i=0;i<(int)adj[u].size();i++)
    {
        int v=adj[u][i].v;
        if(v==fa[u][0])
            continue;
        fa[v][0]=u;
        mn[v][0]=adj[u][i].l;
        lev[v]=lev[u]+1;
        dfs(v);
    }
}

void InitLCA()
{
    for(int j=1;(1<<j)<=n;j++)
        for(int i=1;i<=n;i++)
            if(lev[i]-(1<<j)>=0)
            {
                fa[i][j]=fa[fa[i][j-1]][j-1];
                mn[i][j]=min(mn[i][j-1],mn[fa[i][j-1]][j-1]);
            }
}
int LCA(int a,int b)
{
    if(lev[a]>lev[b])
        swap(a,b);
    for(int j=MAXLOG-1;j>=0;j--)
        if(lev[b]-(1<<j)>=lev[a])
            b=fa[b][j];
    if(a==b)
        return a;
    for(int j=MAXLOG-1;j>=0;j--)
        if(lev[a]-(1<<j)>=0&&fa[a][j]!=fa[b][j])
            a=fa[a][j],b=fa[b][j];
    return fa[a][0];
}
int GetMin(int a,int len)
{
    int res=0x3F3F3F3F;
    for(int j=MAXLOG-1;j>=0;j--)
        if((1<<j)<=len)
        {
            res=min(res,mn[a][j]);
            a=fa[a][j];
            len-=(1<<j);
        }
    return res;
}

bool dfncmp(int a,int b)
{return dfn[a]<dfn[b];}

int k,h[MAXN];
bool flag[MAXN];

int stk[MAXN*2],tp;
int opseq[MAXN*2],cnt;

void AddVTEdge(int a,int b)
{
    vfa[b]=a;
    vson[a].push_back(b);
    opseq[++cnt]=a;
    //printf("%d->%d\n",a,b);
}

long long DP(int u)
{
    long long res=0x3F3F3F3F3F3F3F3FLL;
    if(u!=1)
        res=GetMin(u,lev[u]-lev[vfa[u]]);
    if(flag[u])
        return res;
    long long tmp=0;
    for(int i=0;i<(int)vson[u].size();i++)
        tmp+=DP(vson[u][i]);
    res=min(res,tmp);
    return res;
}

void solve()
{
    for(int i=1;i<=k;i++)
        flag[h[i]]=true;
    flag[1]=false;
    sort(h+1,h+k+1,dfncmp);
    cnt=0;
    stk[tp=1]=h[1];
    for(int i=2;i<=k;i++)
    {
        int l=LCA(h[i],stk[tp]);
        while(tp)
        {
            if(stk[tp]==l)
                break;
            if(tp==1||lev[stk[tp-1]]<lev[l])
            {
                AddVTEdge(l,stk[tp]);
                tp--;
                stk[++tp]=l;
                break;
            }
            AddVTEdge(stk[tp-1],stk[tp]);
            tp--;
        }
        stk[++tp]=h[i];
    }
    while(tp>1)
    {
        AddVTEdge(stk[tp-1],stk[tp]);
        tp--;
    }

    printf("%lld\n",DP(1));

    for(int i=1;i<=cnt;i++)
        vson[opseq[i]].clear();
    for(int i=1;i<=k;i++)
        flag[h[i]]=false;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        adj[a].push_back(Edge(b,c));
        adj[b].push_back(Edge(a,c));
    }

    dfs(1);
    InitLCA();

    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&k);
        for(int j=1;j<=k;j++)
            scanf("%d",&h[j]);
        h[++k]=1;
        solve();
    }

    return 0;
}
