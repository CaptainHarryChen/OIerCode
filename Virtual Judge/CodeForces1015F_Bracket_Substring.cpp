#include<cstdio>
#include<cstring>
const int MAXN=205,MOD=1000000007;

int n,m;
char str[MAXN];
int fail[MAXN],pos[MAXN][2];
int dp[MAXN][MAXN][MAXN][2];

int main()
{
	scanf("%d%s",&n,str+1);
	m=strlen(str+1);
	for(int i=2;i<=m;i++)
	{
		int u=fail[i-1];
		while(u)
		{
			if(str[u+1]==str[i])
			{
				fail[i]=u+1;
				break;
			}
			u=fail[u];
		}
		if(str[u+1]==str[i])
			fail[i]=u+1;
		else
			fail[i]=0;
	}
	for(int i=0;i<m;i++)
		for(int s=0;s<2;s++)
		{
			int u=i;
			while(u)
			{
				if((s==0&&str[u+1]=='(')||(s==1&&str[u+1]==')'))
				{
					pos[i][s]=u+1;
					break;
				}
				u=fail[u];
			}
			if((s==0&&str[u+1]=='(')||(s==1&&str[u+1]==')'))
				pos[i][s]=u+1;
			else
				pos[i][s]=0;
		}
		
	dp[0][0][0][0]=1;
	for(int i=0;i<2*n;i++)
		for(int j=0;j<=n;j++)
			for(int k=0;k<=m;k++)
				for(int f=0;f<2;f++)
					if(dp[i][j][k][f])
					{
						//printf("dp[%d][%d][%d][%d]=%d\n",i,j,k,f,dp[i][j][k][f]);
						if(j>0)
							(dp[i+1][j-1][pos[k][1]][f|(pos[k][1]==m)]+=dp[i][j][k][f])%=MOD;
						(dp[i+1][j+1][pos[k][0]][f|(pos[k][0]==m)]+=dp[i][j][k][f])%=MOD;
					}
	int ans=0;
	for(int k=0;k<=m;k++)
		(ans+=dp[n*2][0][k][1])%=MOD;
	
	printf("%d\n",ans);
	
	return 0;
}
