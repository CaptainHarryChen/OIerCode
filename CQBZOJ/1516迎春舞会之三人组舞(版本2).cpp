#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXM 1005
#define MAXN 5005
int m,n;
int h[MAXN];
int dp[MAXN][MAXN/3];
bool cmp(int a,int b){return a>b;}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]);
	sort(h+1,h+n+1,cmp);
	memset(dp,0x3F,sizeof dp);
	for(int i=1;i<=n;i++)
		dp[i][0]=0;
	for(int i=3;i<=n;i++)
		for(int j=1;j*3<=i;j++)
			dp[i][j]=min(dp[i-1][j],dp[i-2][j-1]+(h[i]-h[i-1])*(h[i]-h[i-1]));
	printf("%d\n",dp[n][m]);
	return 0;
}
