#include<cstdio>
const int MAXN=23;

unsigned long long dp[MAXN][MAXN];

int main()
{
	dp[1][0]=1;
	for(int i=2;i<=21;i++)
	{
		dp[i][0]=dp[i-1][0];
		for(int j=1;j<i;j++)
			dp[i][j]=dp[i-1][j]+dp[i-1][j-1]*(i-1);
	}
	int n,k;
	for(;;)
	{
		scanf("%d%d",&n,&k);
		if(n==0&&k==0)
			break;
		printf("%llu\n",dp[n][k]);
	}
	
	return 0;
}
