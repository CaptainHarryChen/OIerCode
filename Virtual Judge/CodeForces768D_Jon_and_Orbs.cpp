#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXD=8005,MAXK=1005;
double dp[MAXK][MAXD];
int main()
{
	int k,q;
	scanf("%d%d",&k,&q);
	dp[1][1]=1.0;
	for(int i=2;i<MAXD;i++)
		for(int j=1;j<=k;j++)
			dp[j][i]=dp[j][i-1]*j/k+dp[j-1][i-1]*(k-j+1)/k;
	int p;
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&p);
		printf("%d\n",lower_bound(dp[k]+1,dp[k]+MAXD,1.0*p/2000.0)-dp[k]);
	}
	return 0;
}
