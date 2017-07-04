#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 3000000
double dp[MAXN];
int main()
{
	int n,m,i;
	double sum;
	while(~scanf("%d%d",&m,&n))
	{
		dp[0]=1.0;
		sum=1.0;
		for(i=1;i<MAXN&&i<=n;i++)
		{
			dp[i]=sum*(1.0/m);
			if(dp[i-1]-dp[i]<=1e-14&&dp[i]-dp[i-1]<=1e-14)
				break;
			sum+=dp[i];
			if(i>=m)
				sum-=dp[i-m];
		}
		printf("%.5lf\n",dp[min(i,n)]);
	}
	return 0;
}
