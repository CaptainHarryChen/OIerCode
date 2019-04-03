#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const long long MAXN=300005;

struct Edge
{
    long long v,w;
    Edge(){}
    Edge(long long a,long long b){v=a;w=b;}
};
struct Node
{
    long long v,c;
    Node(){}
    Node(long long a,long long b){v=a;c=b;}
    Node operator + (const Node &t)const
    {return Node(v+t.v,c+t.c);}
    Node operator + (long long x)const
    {return Node(v+x,c);}
    bool operator < (const Node &t)const
    {return v<t.v||(v==t.v&&c>t.c);}
};

long long N,K;
vector<Edge> adj[MAXN];
Node dp[MAXN][3];

void DP(long long u,long long fa,long long delta)
{
    dp[u][2]=max(dp[u][2],Node(-delta,1));
    for(long long i=0;i<(long long)adj[u].size();i++)
    {
        long long v=adj[u][i].v;
        if(v==fa)
            continue;
        DP(v,u,delta);
        dp[u][2]=max(dp[u][2]+dp[v][0],dp[u][1]+dp[v][1]+adj[u][i].w+Node(-delta,1));
        dp[u][1]=max(dp[u][1]+dp[v][0],dp[u][0]+dp[v][1]+adj[u][i].w);
        dp[u][0]=dp[u][0]+dp[v][0];
    }
    dp[u][0]=max(dp[u][0],max(dp[u][1]+Node(-delta,1),dp[u][2]));
}

int main()
{
    scanf("%lld%lld",&N,&K);
    K++;
    long long L=0,R=0;
    for(long long i=1,u,v,w;i<N;i++)
    {
        scanf("%lld%lld%lld",&u,&v,&w);
        adj[u].push_back(Edge(v,w));
        adj[v].push_back(Edge(u,w));
        L-=abs(w);
        R+=abs(w);
    }

    long long res=-0x3F3F3F3F3F3F3F3FLL;
    while(L<=R)
    {
        long long mid=(L+R)/2;
        memset(dp,0,sizeof dp);
        DP(1,0,mid);
        if(dp[1][0].c<=K)
            R=mid-1;
        else
            L=mid+1;
    }
    memset(dp,0,sizeof dp);
    DP(1,0,L);
    res=max(res,dp[1][0].v+K*L);
    printf("%lld\n",res);

    return 0;
}
