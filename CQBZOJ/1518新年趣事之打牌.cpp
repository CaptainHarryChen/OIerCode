#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
#define MAXN 105
#define MAXW 100005
int W,n,w[MAXN];
int dp[MAXN][MAXW];
bool used[MAXN];
int main()
{
	scanf("%d%d",&W,&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=W;j++)
		{
			dp[i][j]=dp[i-1][j];
			if(j>=w[i])
				dp[i][j]+=dp[i-1][j-w[i]];
		}
	if(!dp[n][W])
		printf("0");
	else if(dp[n][W]!=1)
		printf("-1");
	else
	{
		int y=W;
		for(int i=n;i>0;i--)
			if(dp[i][y-w[i]])
			{
				used[i]=1;
				y-=w[i];
			}
		bool f=0;
		for(int i=1;i<=n;i++)
			if(!used[i])
			{
				if(f)printf(" ");
				printf("%d",i);
				f=1;
			}
	}
	return 0;
}
