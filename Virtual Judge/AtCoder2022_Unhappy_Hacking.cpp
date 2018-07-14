#include<cstdio>
#include<cstring>
const int MAXN=5005,MOD=1000000007;

char str[MAXN];
long long dp[MAXN][MAXN];

int main()
{
	int N;
	scanf("%d%s",&N,str);
	
	dp[0][0]=1;
	for(int i=1;i<=N;i++)
		for(int j=0;j<=N;j++)
		{
			(dp[i][j]+=dp[i-1][j+1]*2%MOD)%=MOD;
			(dp[i][j]+=dp[i-1][j==0?0:j-1])%=MOD;
		}
	
	printf("%lld\n",dp[N][strlen(str)]);
	
	return 0;
}
