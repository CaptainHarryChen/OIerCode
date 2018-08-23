#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int MAXN=5005;

long long ans;
int n;
vector<int> adj[MAXN];
int dp[MAXN][MAXN];

void DP(int u,int fa=0)
{
    dp[u][0]=1;
    for(int i=0;i<(int)adj[u].size();i++)
        if(adj[u][i]!=fa)
        {
            DP(adj[u][i],u);
            for(int d=0;d<=n;d++)
                dp[u][d+1]+=dp[adj[u][i]][d];
        }
}
void Solve(int u,int fa=0)
{
    ans+=1LL*(adj[u].size()-1)*(adj[u].size()-2)*(adj[u].size()-3)/6;
    if(fa)
    {
        for(int d=1;d<=n;d++)
            ans+=1LL*dp[u][d]*(dp[u][d]-1)/2*(dp[fa][d-1]-(d>=2?dp[u][d-2]:0));
    }
    for(int i=0;i<(int)adj[u].size();i++)
        if(adj[u][i]!=fa)
            Solve(adj[u][i],u);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    DP(1);
    Solve(1);

    printf("%lld\n",ans);

    return 0;
}
