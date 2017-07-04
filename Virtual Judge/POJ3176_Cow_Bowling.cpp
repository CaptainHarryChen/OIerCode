#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 355
int n,num[MAXN][MAXN];
int dp[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			scanf("%d",&num[i][j]);
	dp[1]=num[1][1];
	for(int i=2;i<=n;i++)
		for(int j=n;j>=1;j--)
			dp[j]=max(dp[j],dp[j-1])+num[i][j];
	int ans=0;
	for(int j=1;j<=n;j++)
		ans=max(ans,dp[j]);
	printf("%d\n",ans);
	return 0;
}
