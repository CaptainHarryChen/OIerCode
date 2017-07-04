#include<cstdio>
#include<cstring>
double dp[2][105];
int main()
{
	int c,n,m;
	while(1)
	{
		scanf("%d",&c);
		if(!c)break;
		scanf("%d%d",&n,&m);
		if(m>n||m>c)
		{
			printf("0.000\n");
			continue;
		}
		memset(dp,0,sizeof dp);
		if(n>1005)
			n=n%2?1001:1000;
		dp[0][0]=1;
		for(int i=1;i<=n;i++)
		{
			dp[i&1][0]=dp[!(i&1)][1]/c;
			for(int j=1;j<=c&&j<=i;j++)
				dp[i&1][j]=
				dp[!(i&1)][j-1]*(c-(j-1.0))/c
				+dp[!(i&1)][j+1]*(j+1.0)/c;
		}
		printf("%.3f\n",dp[n&1][m]);
	}
	return 0;
}