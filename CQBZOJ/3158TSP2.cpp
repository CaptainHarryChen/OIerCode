#include<cstdio>
#include<cstring>
#define MAXN 23
#define MAXS ((1<<20)+10)
#define min(a,b) (a>b?b:a)
int n,start,E[MAXN][MAXN],dp[MAXS][MAXN];
int main()
{
	scanf("%d%d",&n,&start);
	start++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&E[i][j]);
	int S=(1<<n)-1;
	memset(dp,127,sizeof dp);
	for(int s=1,i=1;s<=S;s<<=1,i++)dp[s][i]=E[start][i];
	for(int s=1;s<=S;s++)
	{
		if(s&(1<<(start-1)))continue;
		for(int i=1,ss=1;i<=n;i++,ss<<=1)
			if((s&ss)&&i!=start)
				for(int j=1,si=1;j<=n;j++,si<<=1)
					if(j!=i&&(s&si))
						dp[s][i]=min(dp[s][i],dp[s-ss][j]+E[j][i]);
	}
	int mindp=0x7FFFFFFF;
	for(int i=1;i<=n;i++)
		mindp=min(mindp,dp[S-(1<<(start-1))][i]+E[i][start]);
	printf("%d\n",mindp);
	return 0;
}
