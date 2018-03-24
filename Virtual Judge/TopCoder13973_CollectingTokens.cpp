#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=105;

class CollectingTokens
{
	int n,L;
	vector<int> adj[MAXN];
	int val[MAXN];
	int dp[MAXN][MAXN][2];
	
	void DP(int u,int fa=0)
	{
		static int temp[MAXN][2];
		dp[u][0][0]=dp[u][0][1]=val[u];
		for(int i=0;i<(int)adj[u].size();i++)
			if(adj[u][i]!=fa)
			{
				int v=adj[u][i];
				DP(v,u);
				memcpy(temp,dp[u],sizeof temp);
				for(int j=L;j>=1;j--)
					for(int k=j-1;k>=0;k--)
					{
						dp[u][j][0]=max(dp[u][j][0],dp[v][k][0]+temp[j-k-1][1]);
						if(j-k-2>=0)
						{
							dp[u][j][0]=max(dp[u][j][0],dp[v][k][1]+temp[j-k-2][0]);
							dp[u][j][1]=max(dp[u][j][1],dp[v][k][1]+temp[j-k-2][1]);
						}
					}
			}
	}
	
	int solve()
	{
		DP(1);
		int ans=0;
		for(int i=0;i<=L;i++)
			ans=max(ans,dp[1][i][0]);
		return ans;
	}
	
public:
	int maxTokens(vector<int> &A,vector<int> &B,vector<int> &tokens,int _L)
	{
		n=tokens.size();
		for(int i=0;i<n-1;i++)
		{
			adj[A[i]].push_back(B[i]);
			adj[B[i]].push_back(A[i]);
		}
		for(int i=1;i<=n;i++)
			val[i]=tokens[i-1];
		L=_L;
		return solve();
	}
};
