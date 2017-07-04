#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 1005
int n,m;
int map[MAXN][MAXN];
int dp[MAXN][MAXN];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&map[i][j]);
	for(int i=1;i<=n;i++)
		dp[i][1]=map[i][1];
	for(int j=1;j<=m;j++)
		dp[1][j]=map[1][j];
	for(int i=2;i<=n;i++)
		for(int j=2;j<=m;j++)
			if(map[i][j])
			{
				if(map[i-1][j]&&map[i][j-1]&&map[i-1][j-1])
				{
					dp[i][j]=min(dp[i-1][j],dp[i][j-1]);
					dp[i][j]++;
					if(dp[i-1][j]==dp[i][j-1]&&!map[i-dp[i-1][j]][j-dp[i-1][j]])
						dp[i][j]--;
				}
				else
					dp[i][j]=1;
			}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			ans=max(ans,dp[i][j]);
	printf("%d\n",ans);
	return 0;
}
