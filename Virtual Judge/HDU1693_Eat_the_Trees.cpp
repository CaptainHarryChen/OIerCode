#include<cstdio>
#include<cstring>
#define MAXN 13
#define MAXS 5000
bool mat[MAXN][MAXN];
long long dp[MAXN][MAXN][MAXS];
int main()
{
	int T,x,n,m;
	scanf("%d",&T);
	for(int test=1;test<=T;test++)
	{
		scanf("%d%d",&n,&m);
		memset(mat,0,sizeof mat);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				scanf("%d",&x);
				mat[i][j]=(bool)x;
			}
		memset(dp,0,sizeof dp);
		dp[0][m][0]=1;
		for(int i=1;i<=n;i++)
		{
			for(int s=0;s<(1<<m);s++)
				dp[i][0][s<<1]=dp[i-1][m][s];
			for(int j=1;j<=m;j++)
				for(int s=0;s<(1<<(m+1));s++)
				{
					int p=1<<j,q=p>>1;
					bool x=s&p,y=s&q;
					if(mat[i][j])
					{
						dp[i][j][s]=dp[i][j-1][s^p^q];
						if(x!=y)
							dp[i][j][s]+=dp[i][j-1][s];
					}
					else
					{
						if(!x&&!y)
							dp[i][j][s]=dp[i][j-1][s];
						else
							dp[i][j][s]=0;
					}
				}
		}
		printf("Case %d: There are %lld ways to eat the trees.\n",test,dp[n][m][0]);
	}
	return 0;
}
