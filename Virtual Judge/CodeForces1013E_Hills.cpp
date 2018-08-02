#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=5005;

int n;
int a[MAXN];
long long dp[MAXN][MAXN][2];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	a[0]=-0x3FFFFFF;a[n+1]=-0x3FFFFFF;
	memset(dp,0x3F,sizeof dp);
	dp[0][0][0]=dp[1][0][0]=dp[2][0][0]=0;
	dp[2][1][1]=max(a[2]-a[1]+1,0);
	if(a[2]<a[1])
		dp[2][1][0]=0;
	for(int i=3;i<=n+1;i++)
	{
		dp[i][0][0]=0;
		for(int j=1;j<=(i+1)/2;j++)
		{
			dp[i][j][0]=min(dp[i-1][j][0],dp[i-1][j][1]);
			dp[i][j][1]=min(dp[i-2][j-1][1]+max((a[i-3]-1)-(a[i-1]-1),0)+max(a[i]-(a[i-1]-1),0)
							,dp[i-2][j-1][0]+max(a[i-2]-(a[i-1]-1),0)+max(a[i]-(a[i-1]-1),0));
			if(a[i]<a[i-1])
				dp[i][j][0]=min(dp[i][j][0],dp[i][j][1]);
			//printf("dp[%d][%d][0]=%I64d\n",i,j,dp[i][j][0]);
			//printf("dp[%d][%d][1]=%I64d\n",i,j,dp[i][j][1]);
		}
	}
	
	for(int i=1;i<=(n+1)/2;i++)
		printf("%I64d ",dp[n+1][i][0]);
	puts("");
	
	return 0;
}
