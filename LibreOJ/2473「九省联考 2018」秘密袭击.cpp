#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=1670,MOD=64123;

int n,k,W,d[MAXN];
vector<int> adj[MAXN];

bool col[MAXN];
int dp[MAXN][MAXN];

void dfs(int u,int fa)
{
    if(col[u])
        for(int j=0;j<k;j++)
            dp[u][j+1]=dp[fa][j];
    else
        for(int j=0;j<=k;j++)
            dp[u][j]=dp[fa][j];
    for(int i=0;i<(int)adj[u].size();i++)
    {
        int v=adj[u][i];
        if(v==fa)
            continue;
        dfs(v,u);
        for(int j=0;j<=k;j++)
            dp[u][j]=(dp[u][j]+dp[v][j])%MOD;
    }
}

int main()
{
    scanf("%d%d%d",&n,&k,&W);
    for(int i=1;i<=n;i++)
        scanf("%d",&d[i]);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int ans=0;
    for(int rt=1;rt<=n;rt++)
    {
        int cnt=0;
        for(int i=1;i<=n;i++)
            if(d[i]>d[rt]||(d[i]==d[rt]&&i<=rt))
                col[i]=true,cnt++;
            else
                col[i]=false;
        if(cnt<k)
            continue;
        memset(dp,0,sizeof dp);
        dp[0][0]=1;
        dfs(rt,0);
        ans=(ans+1LL*d[rt]*dp[rt][k]%MOD)%MOD;
    }
    printf("%d\n",ans);

    return 0;
}
