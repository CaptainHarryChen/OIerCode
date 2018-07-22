#include<cstdio>
const int MAXN=55,MAXA=50*50*2+10,ZERO=50*50;

int N,A;
int x[MAXN];
long long dp[MAXN][MAXA];

int main()
{
	scanf("%d%d",&N,&A);
	for(int i=1;i<=N;i++)
		scanf("%d",x+i),x[i]-=A;
	
	dp[0][ZERO]=1;
	for(int i=1;i<=N;i++)
	{
		for(int j=0;j<MAXA;j++)
			dp[i][j]=dp[i-1][j];
		for(int j=0;j<MAXA;j++)
			if(j-x[i]>=0&&j-x[i]<MAXA)
				dp[i][j]+=dp[i-1][j-x[i]];
	}
	printf("%lld\n",dp[N][ZERO]-1);

	return 0;
}
