#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=5005,MAXS=2000005,MOD=1000000007;

int N,A,B;
int mn[MAXN],mx[MAXN];
vector<int> adj[MAXN];
vector<bool> st[MAXN];

int dfn[MAXN],low[MAXN],dfc;
bool inst[MAXN];
int stk[MAXN],tp;
int id[MAXN],gcd[MAXN],topo[MAXN],tpit;

void Transform(int u,int v,int g)
{
    for(int j=0;j<(int)st[u].size();j++)
        if(st[u][j])
            st[v][j%g]=1;
}
void Update(int v,int g)
{
    for(int j=g;j<(int)st[v].size();j++)
        st[v][j]=st[v][j]||st[v][j-g];
}

void tarjan(int u)
{
    low[u]=dfn[u]=++dfc;
    stk[++tp]=u;
    inst[u]=true;
    for(auto v:adj[u])
    {
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(inst[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        topo[++tpit]=u;
        int m=tp;
        do
        {
            inst[stk[tp]]=false;
            id[stk[tp]]=tpit;
        }while(stk[tp--]!=u);
        int g=st[u].size();
        for(int i=tp+2;i<=m;i++)
            g=__gcd(g,(int)st[stk[i]].size());
        gcd[tpit]=g;
        for(int i=tp+2;i<=m;i++)
            Transform(stk[i],u,g);
        Update(u,g);
    }
}

int PowMod(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1)
            res=1LL*res*a%MOD;
        b>>=1;
        a=1LL*a*a%MOD;
    }
    return res;
}
int fac[MAXN],ifac[MAXN];
void InitC()
{
    fac[0]=1;
    for(int i=1;i<=N;i++)
        fac[i]=1LL*fac[i-1]*i%MOD;
    ifac[N]=PowMod(fac[N],MOD-2);
    for(int i=N-1;i>=0;i--)
        ifac[i]=1LL*ifac[i+1]*(i+1)%MOD;
}
int C(int n,int r)
{return 1LL*fac[n]*ifac[n-r]%MOD*ifac[r]%MOD;}

char buf[MAXS];

int main()
{
    scanf("%d%d%d",&N,&A,&B);
    for(int i=1;i<=N;i++)
    {
        scanf("%s",buf+1);
        for(int j=1;j<=N;j++)
            if(buf[j]=='1')
                adj[i].push_back(j);
    }
    for(int i=1;i<=N;i++)
    {
        int k;
        scanf("%d%s",&k,buf);
        for(int j=0;j<k;j++)
        {
            st[i].push_back(buf[j]=='1'?1:0);
            mn[i]+=st[i][j];
        }
    }

    for(int i=1;i<=N;i++)
        if(!dfn[i])
            tarjan(i);

    for(int i=tpit;i>1;i--)
    {
        int g=__gcd(gcd[i],gcd[i-1]);
        Transform(topo[i],topo[i-1],g);
        Update(topo[i-1],g);
    }

    for(int i=1;i<=N;i++)
        if(topo[id[i]]==i)
            for(int j=0;j<(int)st[i].size();j++)
                mx[i]+=st[i][j];
    for(int i=1;i<=N;i++)
        if(topo[id[i]]!=i)
            mx[i]=1LL*mx[topo[id[i]]]*st[i].size()/st[topo[id[i]]].size();

    //for(int i=1;i<=N;i++)
    //    printf("mn[%d]=%d;mx[%d]=%d;\n",i,mn[i],i,mx[i]);

    InitC();

    int ans=0;
    for(int i=1;i<=N;i++)
    {
        int must=0,can=0;
        for(int j=1;j<=N;j++)
            if(mn[j]>mx[i])
                must++;
        if(must>=A)
            continue;
        for(int j=1;j<=N;j++)
            if(mn[j]<=mx[i]&&(mx[j]>mx[i]||(mx[j]==mx[i]&&j>i)))
                can++;
        for(int k=max(0,B-1-must);k<=B-1&&k<=can&&k<=A-1-must;k++)
            ans=(ans+1LL*C(can,k)*C(must,B-1-k)%MOD)%MOD;
    }
    printf("%d\n",ans);

    return 0;
}
