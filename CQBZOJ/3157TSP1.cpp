#include<cstdio>
#include<cstring>
#define MAXN 23
#define MAXS ((1<<20)+10)
#define min(a,b) (a>b?b:a)
int n,E[MAXN][MAXN],dp[MAXS][MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&E[i][j]);
	int S=(1<<n)-1;
	memset(dp,127,sizeof dp);
	for(int s=1,i=1;s<=S;s<<=1,i++)dp[s][i]=0;
	for(int s=1;s<=S;s++)
		for(int i=1;i<=n;i++)
			if(s&(1<<(i-1)))
				for(int j=1,si=1;j<=n;j++,si<<=1)
					if(j!=i&&(s&si))
						dp[s][i]=min(dp[s][i],dp[s-(1<<(i-1))][j]+E[j][i]);
	int mindp=0x7FFFFFFF;
	for(int i=1;i<=n;i++)
		mindp=min(mindp,dp[S][i]);
	printf("%d\n",mindp);
	return 0;
}
