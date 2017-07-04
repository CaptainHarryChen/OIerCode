#include<cstdio>
#define MAXN 1000005
#define MOD 1000000000
int dp[MAXN];
int n;
int main()
{
	scanf("%d",&n);
	dp[0]=dp[1]=1;
	for(int i=2;i<=n;i++)
		if(i%2)
			dp[i]=dp[i-1];
		else
			dp[i]=(dp[i-1]+dp[i/2])%MOD;
	printf("%d\n",dp[n]);
	return 0;
}
