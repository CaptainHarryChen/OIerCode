#include<cstdio>
int dp[205][10];
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		dp[i][1]=1;
	for(int i=2;i<=n;i++)
		for(int j=2;j<=i&&j<=k;j++)
			dp[i][j]=dp[i-j][j]+dp[i-1][j-1];
	printf("%d\n",dp[n][k]);
	return 0;
}
