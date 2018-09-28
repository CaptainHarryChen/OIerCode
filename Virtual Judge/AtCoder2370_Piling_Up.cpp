#include<cstdio>
const int MAXN=3005,MOD=1000000007;

int N,M;
int dp[MAXN][MAXN][2];

int main()
{
	scanf("%d%d",&N,&M);
	dp[0][0][1]=1;
	for(int i=1;i<=N;i++)
		dp[0][i][0]=1;
	for(int i=0;i<M;i++)
		for(int j=0;j<=N;j++)
			for(int k=0;k<2;k++)
			{
				if(j>0)
				{
					(dp[i+1][j-1][k|(j==1)]+=dp[i][j][k])%=MOD;
					(dp[i+1][j][k|(j==1)]+=dp[i][j][k])%=MOD;
				}
				if(j<N)
				{
					(dp[i+1][j+1][k]+=dp[i][j][k])%=MOD;
					(dp[i+1][j][k]+=dp[i][j][k])%=MOD;
				}
			}
	int ans=0;
	for(int j=0;j<=N;j++)
		(ans+=dp[M][j][1])%=MOD;
	printf("%d\n",ans);
	
	return 0;
}
