#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define INF 2139062143
#define MAXN 500500
int n,num[MAXN],dp[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
	for(int i=1;i<=n;i++)
		dp[i]=max(dp[i-1]+num[i],num[i]);
	int maxsum=0;
	for(int i=1;i<=n;i++)
		maxsum=max(maxsum,dp[i]);
	printf("%d\n",maxsum);
	return 0;
}
