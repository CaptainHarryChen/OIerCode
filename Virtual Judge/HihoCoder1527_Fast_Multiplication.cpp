#include<cstdio>
#include<bitset>
using namespace std;
const int MAXN=1000005;

int dp[MAXN][2];
bitset<MAXN> a[2];

int main()
{
	int x,n;
	for(n=0;scanf("%1d",&x)!=EOF;n++)
		a[0][n]=x;
	a[1]=(~a[0]);
	for(int i=n-1;i>=0;i--)
	{
		if(a[1][i])
			a[1][i]=0;
		else
		{
			a[1][i]=1;
			break;
		}
	}
	dp[n-1][0]=a[0][n-1]*2;
	dp[n-1][1]=a[1][n-1]*2;
	for(int i=n-2;i>=0;i--)
	{
		if(a[0][i])
			dp[i][0]=dp[i+1][0]+2;
		else
			dp[i][0]=min(dp[i+1][0],dp[i+1][1]+2);
		if(a[1][i])
			dp[i][1]=dp[i+1][1]+2;
		else
			dp[i][1]=min(dp[i+1][1],dp[i+1][0]+2);
	}
	int ans=min(dp[0][0]-1,dp[0][1]+1);
	printf("%d\n",ans);
	return 0;
}
