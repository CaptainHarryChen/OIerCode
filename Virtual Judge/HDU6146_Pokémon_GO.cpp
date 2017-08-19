#include<cstdio>
#include<cstring>
const int MAXN=10005;
const long long MOD=1000000007LL;
int dp[MAXN][2];
int main()
{
	int T,n;
	long long ans;
	dp[0][0]=1;
	dp[0][1]=1;
	dp[1][0]=2;
	dp[1][1]=2;
	for(n=2;n<=10000;n++)
	{
		dp[n][0]=((dp[n-1][0]*2LL)%MOD+(dp[n-1][1]*2LL)%MOD+(dp[n-2][0]*4LL)%MOD)%MOD;
		dp[n][1]=(dp[n-1][1]*2LL)%MOD;
	}
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		if(n==1)
			printf("2\n");
		else
		{
			ans=0;
			ans=(ans+dp[n][0])%MOD;
			for(int i=2;i<n;i++)
			{
				ans=(ans+(2LL*dp[i-1][1]*dp[n-i][0])%MOD)%MOD;
				ans=(ans+(2LL*dp[n-i][1]*dp[i-1][0])%MOD)%MOD;
			}
			ans=(ans+dp[n][0])%MOD;
			printf("%I64d\n",ans);
		}
	}
	return 0;
}
