#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=305;

int N,M,K;

struct Edge
{
	int v,w;
	Edge(int _v,int _w){v=_v;w=_w;}
};

vector<Edge> adj[MAXN];
int dp[MAXN][MAXN][2];
int siz[MAXN];

void DP(int u,int fa=0)
{
	static int temp[MAXN][2];
	dp[u][0][0]=dp[u][1][1]=0;
	siz[u]=1;
	for(int p=0;p<(int)adj[u].size();p++)
		if(adj[u][p].v!=fa)
		{
			int v=adj[u][p].v;
			DP(v,u);
			siz[u]+=siz[v];
			memcpy(temp,dp[u],sizeof dp[u]);
			for(int j=siz[u];j>=0;j--)
			{
				dp[u][j][0]=dp[u][j][1]=100000000;
				if(j>0)
					for(int k=0;k<j;k++)
					{
						dp[u][j][1]=min(dp[u][j][1],temp[j-k][1]+dp[v][k][1]+adj[u][p].w);
						dp[u][j][1]=min(dp[u][j][1],temp[j-k][1]+dp[v][k][0]);
					}
				for(int k=0;k<=j;k++)
				{
					dp[u][j][0]=min(dp[u][j][0],temp[j-k][0]+dp[v][k][0]+(M==2)*adj[u][p].w);
					dp[u][j][0]=min(dp[u][j][0],temp[j-k][0]+dp[v][k][1]);
				}
			}
		}
}

int main()
{
	scanf("%d%d%d",&N,&M,&K);
	if(N-K<M-1)
	{
		puts("-1");
		return 0;
	}
	for(int i=1,a,b,c;i<N;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		adj[a].push_back(Edge(b,c));
		adj[b].push_back(Edge(a,c));
	}
	
	for(int i=1;i<=N;i++)
		for(int j=0;j<=K;j++)
			dp[i][j][0]=dp[i][j][1]=100000000;
	DP(1);

	printf("%d\n",dp[1][K][1]);
	
	return 0;
}
