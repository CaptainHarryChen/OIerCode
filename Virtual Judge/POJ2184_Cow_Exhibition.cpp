#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 105
#define MAXW 1005
int dp[MAXN][MAXN*MAXW];
int N;
struct cow{int S,F;}c[MAXN];
bool cmp(cow a,cow b){return a.S>b.S;}
int main()
{
	scanf("%d",&N);
	int mxS=0;
	for(int i=1;i<=N;i++)
	{
		scanf("%d%d",&c[i].S,&c[i].F);
		mxS+=max(c[i].S,0);
	}
	sort(c+1,c+N+1,cmp);
	memset(dp,0x8F,sizeof dp);
	int i;
	for(i=1;i<=N&&c[i].S>=0;i++)
	{
		for(int j=1;j<=mxS;j++)
			dp[i][j]=dp[i-1][j];
		dp[i][c[i].S]=max(dp[i][c[i].S],c[i].F);
		for(int j=c[i].S+1;j<=mxS;j++)
			dp[i][j]=max(dp[i][j],dp[i-1][j-c[i].S]+c[i].F);
	}
	for(;i<=N;i++)
	{
		for(int j=1;j<=mxS;j++)
			dp[i][j]=dp[i-1][j];
		for(int j=mxS+c[i].S;j>=0;j--)
			dp[i][j]=max(dp[i][j],dp[i-1][j-c[i].S]+c[i].F);
	}
	int ans=0;
	for(int j=1;j<=mxS;j++)
		if(dp[N][j]>=0)
			ans=max(ans,j+dp[N][j]);
	printf("%d\n",ans);
	return 0;
}
