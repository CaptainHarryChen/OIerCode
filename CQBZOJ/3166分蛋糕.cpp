#include<cstdio>
#include<cstring>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?b:a)
#define MAXN 45
int w,h,m,dp[MAXN][MAXN][MAXN];
int main()
{
	scanf("%d%d%d",&w,&h,&m);
	memset(dp,127,sizeof dp);
	for(int i=1;i<=w;i++)
		for(int j=1;j<=h;j++)
		{
			dp[i][j][1]=i*j;
			for(int k=2;k<=m;k++)
			{
				for(int pi=1;pi<i;pi++)
					for(int n=1;n<k;n++)
						dp[i][j][k]=min(dp[i][j][k],max(dp[pi][j][n],dp[i-pi][j][k-n]));
				for(int qi=1;qi<j;qi++)
					for(int n=1;n<k;n++)
						dp[i][j][k]=min(dp[i][j][k],max(dp[i][qi][n],dp[i][j-qi][k-n]));
			}
		}
	printf("%d\n",dp[w][h][m]);
	return 0;
}
