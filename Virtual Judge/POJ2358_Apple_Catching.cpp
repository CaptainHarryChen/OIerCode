#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXT 1005
#define MAXW 33
int T,W;
int dp[MAXT][MAXW][2];
int ap[MAXT];
int main()
{
	scanf("%d%d",&T,&W);
	for(int i=1;i<=T;i++)
		scanf("%d",ap+i);
	for(int i=1;i<=T;i++)
		for(int j=W;j>=0;j--)
			for(int k=0;k<2;k++)
				dp[i][j][k]=max(dp[i-1][j][k],j==W?0:dp[i-1][j+1][k^1])+(ap[i]==(k+1));
	int ans=0;
	for(int j=W;j>=0;j--)
		for(int k=0;k<2;k++)
			ans=max(ans,dp[T][j][k]);
	printf("%d\n",ans);
	return 0;
}
