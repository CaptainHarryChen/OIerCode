#include<cstdio>
#include<cstring>
#define MAXN 1005
#define min(a,b) (a>b?b:a)
int main()
{
	int n;
	double pl,pr,dp[MAXN];
	while(1)
	{
		scanf("%d",&n);
		if(!n)break;
		scanf("%lf%lf",&pl,&pr);
		dp[1]=1/(1-pl-pr);
		for(int i=2;i<=n;i++)
		{
			dp[i]=1e100;
			for(int j=0;j<i;j++)
				dp[i]=min(dp[i],dp[j]+dp[i-1-j]+(1+dp[j]*pl+dp[i-1-j]*pr)/(1-pl-pr));
		}
		printf("%.2lf\n",dp[n]);
	}
	return 0;
}
