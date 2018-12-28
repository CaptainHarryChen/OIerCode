#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int n,A[MAXN],dp[MAXN][35];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	for(int i=1;i<=n;i++)
	{
		int mx=0;
		for(int j=0;j<31;j++)
			if(A[i]&(1<<j))
				mx=max(mx,dp[i-1][j]);
		for(int j=0;j<31;j++)
			if(A[i]&(1<<j))
				dp[i][j]=mx+1;
			else
				dp[i][j]=dp[i-1][j];
	}
	int ans=0;
	for(int j=0;j<31;j++)
		ans=max(ans,dp[n][j]);
	printf("%d\n",ans);
	
	return 0;
}
