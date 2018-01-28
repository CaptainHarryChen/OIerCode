#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1005;

int col[MAXN][MAXN],row[MAXN][MAXN];
int dp[MAXN][MAXN];
int A[MAXN][MAXN];

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&A[i][j]);
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(i==1||A[i-1][j]+1==A[i][j])
				col[i][j]=col[i-1][j]+1;
			else
				col[i][j]=1;
			if(j==1||A[i][j-1]+1==A[i][j])
				row[i][j]=row[i][j-1]+1;
			else
				row[i][j]=1;
			dp[i][j]=min(dp[i-1][j-1]+1,min(col[i][j],row[i][j]));
			ans=max(ans,dp[i][j]);
		}
	printf("%d\n",ans);
	return 0;
}
