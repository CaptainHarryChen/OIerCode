#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=300005,MAXLOG=20;

int n,m;
vector<int> adj[MAXN];

int vfa[MAXN];
vector<int> vson[MAXN];

int lev[MAXN],dfn[MAXN],dfc;
int siz[MAXN];
int fa[MAXN][MAXLOG];

void dfs(int u)
{
    dfn[u]=++dfc;
    siz[u]=1;
    for(int i=0;i<(int)adj[u].size();i++)
    {
        int v=adj[u][i];
        if(v==fa[u][0])
            continue;
        fa[v][0]=u;
        lev[v]=lev[u]+1;
        dfs(v);
        siz[u]+=siz[v];
    }
}

void InitLCA()
{
    for(int j=1;(1<<j)<=n;j++)
        for(int i=1;i<=n;i++)
            if(lev[i]-(1<<j)>=0)
                fa[i][j]=fa[fa[i][j-1]][j-1];
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
int GetKthFa(int x,int k)
{
    for(int j=MAXLOG-1;j>=0;j--)
        if((1<<j)<=k)
            x=fa[x][j],k-=(1<<j);
    return x;
}

bool dfncmp(int a,int b)
{return dfn[a]<dfn[b];}

int k,h[MAXN];
int pos[MAXN];
int ans[MAXN];

int stk[MAXN*2],tp;
int id[MAXN*2],cnt;

void AddVTEdge(int a,int b)
{
    vfa[b]=a;
    vson[a].push_back(b);
    //printf("%d->%d\n",a,b);
}

bool flag[MAXN];
int dis[MAXN],go[MAXN];

void dfs1(int u)
{
    if(flag[u])
        dis[u]=0,go[u]=u;
    for(int i=0;i<(int)vson[u].size();i++)
    {
        int v=vson[u][i];
        dfs1(v);
        if(dis[u]>dis[v]+lev[v]-lev[u]||(dis[u]==dis[v]+lev[v]-lev[u]&&go[u]>go[v]))
            dis[u]=dis[v]+lev[v]-lev[u],go[u]=go[v];
    }
}
void dfs2(int u)
{
    if(flag[u])
        dis[u]=0,go[u]=u;
    if(vfa[u])
        if(dis[u]>dis[vfa[u]]+lev[u]-lev[vfa[u]]||(dis[u]==dis[vfa[u]]+lev[u]-lev[vfa[u]]&&go[u]>go[vfa[u]]))
            dis[u]=dis[vfa[u]]+lev[u]-lev[vfa[u]],go[u]=go[vfa[u]];
    for(int i=0;i<(int)vson[u].size();i++)
        dfs2(vson[u][i]);
}
void calcans(int u)
{
    if(vfa[u])
        ans[pos[go[vfa[u]]]]-=siz[GetKthFa(u,lev[u]-lev[vfa[u]]-1)];
    if(vfa[u]&&vfa[u]!=fa[u][0])
    {
        int a=fa[u][0],b=GetKthFa(u,lev[u]-lev[vfa[u]]-1);
        int x=(lev[a]-lev[b]+1+dis[vfa[u]]-dis[u]+1-(go[u]>go[vfa[u]]))/2;
        int mid=GetKthFa(u,x);
        ans[pos[go[u]]]+=siz[mid]-siz[u];
        ans[pos[go[vfa[u]]]]+=siz[b]-siz[mid];
    }
    ans[pos[go[u]]]+=siz[u];
    for(int i=0;i<(int)vson[u].size();i++)
        calcans(vson[u][i]);
}

void solve()
{
    for(int i=1;i<=k;i++)
        flag[h[i]]=true,ans[i]=0,pos[h[i]]=i;
    sort(h+1,h+k+1,dfncmp);
    cnt=0;
    stk[tp=1]=h[1];
    id[++cnt]=h[1];
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
                id[++cnt]=l;
                break;
            }
            AddVTEdge(stk[tp-1],stk[tp]);
            tp--;
        }
        stk[++tp]=h[i];
        id[++cnt]=h[i];
    }
    while(tp>1)
    {
        AddVTEdge(stk[tp-1],stk[tp]);
        tp--;
    }

    for(int i=1;i<=cnt;i++)
        dis[id[i]]=0x3F3F3F3F;
    dfs1(stk[1]);
    dfs2(stk[1]);
    calcans(stk[1]);
    ans[pos[go[stk[1]]]]+=n-siz[stk[1]];
    for(int i=1;i<=k;i++)
        printf("%d%c",ans[i]," \n"[i==k]);

    for(int i=1;i<=cnt;i++)
        vson[id[i]].clear(),vfa[id[i]]=0;
    for(int i=1;i<=k;i++)
        flag[h[i]]=false;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1);
    InitLCA();

    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&k);
        for(int j=1;j<=k;j++)
            scanf("%d",&h[j]);
        solve();
    }

    return 0;
}
