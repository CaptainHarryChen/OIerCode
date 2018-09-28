#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=15,MAXS=(1<<12)+10;

int n,m,G[MAXN][MAXN],adj[MAXN];
int dp[MAXN][MAXS];
int dis[MAXS];
int id[MAXS];

int main()
{
    scanf("%d%d",&n,&m);
    memset(G,0x3F,sizeof G);
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        adj[u]|=(1<<(v-1));
        adj[v]|=(1<<(u-1));
        G[u][v]=min(G[u][v],w);
        G[v][u]=min(G[v][u],w);
    }

    for(int i=1;i<=n;i++)
        id[1<<(i-1)]=i;

    memset(dp,0x3F,sizeof dp);
    for(int i=1;i<=n;i++)
        dp[0][1<<(i-1)]=0;

    for(int i=0;i<n;i++)
        for(int s=1;s<(1<<n);s++)
            if(dp[i][s]!=0x3F3F3F3F)
            {
                int mask=0;
                for(int j=s;j>0;j^=(j&(-j)))
                    mask|=adj[id[j&(-j)]];
                mask&=(~s);
                dis[0]=0;
                for(int j=mask;j>0;j^=(j&(-j)))
                {
                    dis[j&(-j)]=0x3F3F3F3F;
                    for(int k=adj[id[j&(-j)]]&s;k>0;k^=(k&(-k)))
                        dis[j&(-j)]=min(dis[j&(-j)],G[id[j&(-j)]][id[k&(-k)]]*(i+1));
                }
                for(int ts=1;ts<=mask;ts++)
                    if((mask|ts)==mask)
                        dis[ts]=dis[ts^(ts&(-ts))]+dis[ts&(-ts)];

                for(int ts=mask;ts>0;ts=(ts-1)&mask)
                    dp[i+1][s|ts]=min(dp[i+1][s|ts],dp[i][s]+dis[ts]);
            }

    int ans=0x3F3F3F3F;
    for(int i=1;i<=n;i++)
        ans=min(ans,dp[i][(1<<n)-1]);
    printf("%d\n",ans);

    return 0;
}
