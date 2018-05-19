#include<cstdio>
#include<cstring>
const int MAXN=105,MAXM=100005;

int A[MAXN],C[MAXN];
int dp[2][MAXM];


int main()
{
	int n,m;
	for(;;)
	{
		scanf("%d%d",&n,&m);
		if(!n&&!m)
			break;
		for(int i=1;i<=n;i++)
			scanf("%d",A+i);
		for(int i=1;i<=n;i++)
			scanf("%d",C+i);
		
		memset(dp,-1,sizeof dp);
		dp[0][0]=0;
		for(int i=1;i<=n;i++)
		{
			dp[i&1][0]=C[i];
			for(int j=1;j<=m;j++)
			{
				if(dp[(i^1)&1][j]>=0)
					dp[i&1][j]=C[i];
				else if(j>=A[i]&&dp[i&1][j-A[i]]>0)
					dp[i&1][j]=dp[i&1][j-A[i]]-1;
			}
		}
		
		int ans=0;
		for(int i=1;i<=m;i++)
			ans+=(dp[n&1][i]>=0);
		
		printf("%d\n",ans);
	}
	
	return 0;
}
