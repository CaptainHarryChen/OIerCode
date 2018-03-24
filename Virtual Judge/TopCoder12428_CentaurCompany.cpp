#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=40;

class CentaurCompany
{
	int n;
	vector<int> adj[MAXN];
	long long dp[MAXN][MAXN][MAXN][2],temp[MAXN][MAXN][2];
	int siz[MAXN];
	
	void DP(int u,int fa=0)
	{
		siz[u]=1;
		dp[u][0][0][0]=1;
		dp[u][1][1][1]=1;
		for(int i=0;i<(int)adj[u].size();i++)
			if(adj[u][i]!=fa)
			{
				int v=adj[u][i];
				DP(v,u);
				siz[u]+=siz[v];
				memcpy(temp,dp[u],sizeof temp);
				memset(dp[u],0,sizeof dp[u]);
				for(int j=0;j<=siz[u];j++)
					for(int k=0;k<=j;k++)
					{
						for(int j1=0;j1<=j;j1++)
							for(int k1=0;k1<=k&&k1<=j1;k1++)
							{
								dp[u][j][k][0]+=temp[j-j1][k-k1][0]*dp[v][j1][k1][0];
								dp[u][j][k][0]+=temp[j-j1][k-k1][0]*dp[v][j1][k1][1];
								if(j1<j)
								{
									dp[u][j][k][1]+=temp[j-j1][k-k1][1]*dp[v][j1][k1][0];
									dp[u][j][k][1]+=temp[j-j1][k-k1+1][1]*dp[v][j1][k1][1];
								}
							}
					}
			}
	}
	
	double solve()
	{
		memset(dp,0,sizeof dp);
		DP(1);
		/*
		for(int i=1;i<=n;i++)
			for(int j=0;j<=siz[i];j++)
				for(int k=0;k<=j;k++)
					for(int p=0;p<2;p++)
						printf("dp[%d][%d][%d][%d]=%3I64d\n",i,j,k,p,dp[i][j][k][p]);
		*/
		double ans=0;
		for(int j=0;j<=siz[1];j++)
			for(int k=0;k<=j;k++)
				ans+=(1.0*dp[1][j][k][0]+dp[1][j][k][1])/(1.0*(1LL<<n))*max(0.0,k*2.0-2.0-j);
		ans*=2.0;
		return ans;
	}
	
public:
	double getvalue(vector<int> &a,vector<int> &b)
	{
		n=a.size()+1;
		for(int i=0;i<n-1;i++)
		{
			adj[a[i]].push_back(b[i]);
			adj[b[i]].push_back(a[i]);
		}
		return solve();
	}
};
