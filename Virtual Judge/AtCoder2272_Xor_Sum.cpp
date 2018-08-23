#include<cstdio>
#include<map>
using namespace std;
const int MOD=1000000007;

map<long long,long long> dp;
long long DP(long long n)
{
	if(dp[n])
		return dp[n];
	dp[n]=(DP(n/2)+DP((n-1)/2)+DP((n-2)/2))%MOD;
	return dp[n];
}

int main()
{
	dp[0]=1;
	dp[1]=2;
	long long n;
	scanf("%lld",&n);
	printf("%lld\n",DP(n));
	return 0;
}
