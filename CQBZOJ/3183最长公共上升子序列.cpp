#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 5005
int N,M,dp[MAXN];
long long A[MAXN],B[MAXN];
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%lld",&A[i]);
	scanf("%d",&M);
	for(int i=1;i<=M;i++)
		scanf("%lld",&B[i]);
	for(int i=1,k;i<=N;i++)
	{
		k=0;
		for(int j=1;j<=M;j++)
			if(A[i]==B[j])
				dp[j]=max(dp[k]+1,dp[j]);
			else if(A[i]>B[j])
				if(dp[k]<dp[j])
					k=j;
	}
	int ans=0;
	for(int i=1;i<=M;i++)
		ans=max(ans,dp[i]);
	printf("%d\n",ans);
	return 0;
}
