#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 2005
int dp[MAXN][MAXN],mn[MAXN][MAXN];
int N,A[MAXN];
int h[MAXN];
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",A+i);
		h[i]=A[i];
	}
	sort(h+1,h+N+1);
	memset(mn,0x7F,sizeof mn);
	for(int j=0;j<=N;j++)
		mn[0][j]=0;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
		{
			dp[i][j]=mn[i-1][j]+abs(h[j]-A[i]);
			mn[i][j]=min(mn[i][j-1],dp[i][j]);
		}
	printf("%d\n",mn[N][N]);
	return 0;
}
