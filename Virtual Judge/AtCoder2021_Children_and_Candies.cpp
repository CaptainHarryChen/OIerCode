#include<cstdio>
#include<cstring>
const int MAXN=405,MOD=1000000007;

int N,C;
long long mpow[MAXN][MAXN],sum[MAXN][MAXN],dp[MAXN][MAXN];
int A[MAXN],B[MAXN];

int main()
{
	for(int i=1;i<MAXN;i++)
	{
		mpow[i][0]=1;
		for(int j=1;j<MAXN;j++)
			mpow[i][j]=(mpow[i][j-1]*i)%MOD;
	}
	
	scanf("%d%d",&N,&C);
	for(int i=1;i<=N;i++)
		scanf("%d",&A[i]);
	for(int i=1;i<=N;i++)
		scanf("%d",&B[i]);
		
	for(int i=0;i<=C;i++)
		for(int j=1;j<=N;j++)
			for(int k=A[j];k<=B[j];k++)
				sum[i][j]=(sum[i][j]+mpow[k][i])%MOD;
	
	dp[0][0]=1;
	for(int i=1;i<=N;i++)
		for(int j=0;j<=C;j++)
			for(int k=0;k<=j;k++)
				dp[i][j]=(dp[i][j]+dp[i-1][j-k]*sum[k][i]%MOD)%MOD;
	
	printf("%lld\n",dp[N][C]);
	
	return 0;
}
