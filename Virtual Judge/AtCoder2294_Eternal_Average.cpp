#include<cstdio>
const int MAXN=4005,MOD=1000000007;

int N,M,K;
int dp[MAXN][MAXN],sum[MAXN][MAXN];

int main()
{
	scanf("%d%d%d",&N,&M,&K);
	dp[0][0]=1;
	for(int i=1;i<N+M;i++)
		for(int j=0;j<=M;j++)
		{
			sum[i][j]=((j>0?sum[i][j-1]:0)+dp[i-1][j])%MOD;
			dp[i][j]=(sum[i][j]-(j-K>=0?sum[i][j-K]:0)+MOD)%MOD;
		}
	int ans=0;
	while(M>0)
	{
		ans=(ans+dp[(N+M-1)/(K-1)][M])%MOD;
		M-=K-1;
	}
	printf("%d\n",ans);
	
	return 0;
}
