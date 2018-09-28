#include<cstdio>
const int MAXN=1005,MAXM=205,MOD=1000000007;

int N,M,K;
char A[MAXN],B[MAXN];
int dp[2][MAXM][MAXM],sum[2][MAXM][MAXM];

int main()
{
	scanf("%d%d%d%s%s",&N,&M,&K,A+1,B+1);
	dp[0][0][0]=sum[0][0][0]=1;
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=M&&j<=i;j++)
		{
			if(A[i]==B[j])
			{
				for(int k=1;k<=K&&k<=j;k++)
				{
					dp[i&1][j][k]=(sum[(i&1)^1][j-1][k-1]+dp[(i&1)^1][j-1][k])%MOD;
					//fprintf(stderr,"dp[%d][%d][%d]=%d\n",i,j,k,dp[i][j][k]);
				}
			}
		}
		for(int j=0;j<=M&&j<=i;j++)
			for(int k=0;k<=K&&k<=j;k++)
			{
				sum[i&1][j][k]=(sum[(i&1)^1][j][k]+dp[i&1][j][k])%MOD;
				sum[(i&1)^1][j][k]=0;
				dp[(i&1)^1][j][k]=0;
			}
	}
	printf("%d\n",sum[N&1][M][K]);

	return 0;
}
