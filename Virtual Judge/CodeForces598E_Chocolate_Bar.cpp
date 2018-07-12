#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=33,MAXK=53;

long long dp[MAXN][MAXN][MAXK];

int main()
{
	memset(dp,0x3F,sizeof dp);
	for(int i=1;i<=30;i++)
		for(int j=1;j<=30;j++)
		{
			dp[i][j][0]=0;
			if(i*j<=50)
				dp[i][j][i*j]=0;
			for(int k=min(i*j-1,50);k>=1;k--)
			{
				for(int cut=1;cut<i;cut++)
					for(int k2=0;k2<=j*cut&&k2<=k;k2++)
						dp[i][j][k]=min(dp[i][j][k],dp[cut][j][k2]+dp[i-cut][j][k-k2]+1LL*j*j);
				for(int cut=1;cut<j;cut++)
					for(int k2=0;k2<=i*cut&&k2<=k;k2++)
						dp[i][j][k]=min(dp[i][j][k],dp[i][cut][k2]+dp[i][j-cut][k-k2]+1LL*i*i);
			}
		}
	int T,n,m,K;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&n,&m,&K);
		printf("%I64d\n",dp[n][m][K]);
	}
	return 0;
}
