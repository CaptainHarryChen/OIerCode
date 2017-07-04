#include<bits/stdc++.h>
using namespace std;
#define MAXN 33
#define MAXV 20010
int v,n,w[MAXN],dp[MAXV];
int main()
{
	scanf("%d%d",&v,&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	for(int i=1;i<=n;i++)
		for(int j=v;j>=w[i];j--)
			if(dp[j-w[i]]!=0||j==w[i])
				dp[j]=max(dp[j],dp[j-w[i]]+w[i]);
	int ans=0;
	for(int i=1;i<=v;i++)
		ans=max(ans,dp[i]);
	printf("%d\n",v-ans);
	return 0;
}
