#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=300005,MOD=1000000007;

char S[MAXN];
long long dp[MAXN][6],ans;

int main()
{
	scanf("%s",S+1);
	int n=strlen(S+1);
	if(n==1)
	{
		printf("%d\n",S[1]!='0');
		return 0;
	}
	dp[1][0]=1;
	for(int i=1;i<=n;i++)
	{
		if(S[i]=='?')
			(ans*=2)%=MOD;
		for(int j=0;j<6;j++)
		{
			if(dp[i][j]==0)
				continue;
			if(S[i]!='1')//0
			{
				if(j==0)(dp[i+1][2]+=dp[i][j])%=MOD;
				if(j==1)(dp[i+1][4]+=dp[i][j])%=MOD;
				if(j==2)(dp[i+1][3]+=dp[i][j])%=MOD;
				if(j==3)(dp[i+1][2]+=dp[i][j])%=MOD;
				if(j==4)(dp[i+1][5]+=dp[i][j])%=MOD;
				if(j==5)(dp[i+1][4]+=dp[i][j])%=MOD;
			}
			if(S[i]!='0')//1
			{
				if(j==0)(dp[i+1][1]+=dp[i][j])%=MOD;
				if(j==1)(ans+=dp[i][j])%=MOD;
				if(j==2)(dp[i+1][0]+=dp[i][j])%=MOD;
				if(j==3)(dp[i+1][2]+=dp[i][j])%=MOD;
				if(j==4)(dp[i+1][1]+=dp[i][j])%=MOD;
				if(j==5)(dp[i+1][4]+=dp[i][j])%=MOD;
			}
			dp[i][j]%=MOD;
			//printf("dp[%d][%d]=%I64d\n",i,j,dp[i][j]);
		}
	}
	(ans+=dp[n+1][1])%=MOD;
	printf("%lld\n",ans);
	
	return 0;
}
