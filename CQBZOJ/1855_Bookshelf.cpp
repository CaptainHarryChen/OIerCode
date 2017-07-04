#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define MAXN 2016
int N,L,h[MAXN],w[MAXN],dp[MAXN];
int main()
{
	scanf("%d%d",&N,&L);
	for(int i=1;i<=N;i++)
		scanf("%d%d",&h[i],&w[i]);
	memset(dp,0x7F,sizeof dp);
	dp[0]=0;
	dp[1]=h[1];
	for(int i=2;i<=N;i++)
		for(int j=i-1,h_max=h[i],width=w[i];j>=0&&width<=L;j--,h_max=max(h_max,h[j+1]),width+=w[j+1])
			dp[i]=min(dp[i],dp[j]+h_max);
	printf("%d\n",dp[N]);
	return 0;
}
