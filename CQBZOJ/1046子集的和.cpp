#include<bits/stdc++.h>
using namespace std;
#define MAXW 900
long long n,w,dp[MAXW];
int main()
{
	scanf("%lld",&n);
	w=(n+1)*n/2;
	if(w%2){printf("0\n");return 0;}
	w/=2;
	for(long long i=1;i<=n;i++)
		for(long long j=w;j>=i;j--)
		{
			if(dp[j-i]>0)
				dp[j]+=dp[j-i];
			if(i==j)
				dp[j]++;
		}
	printf("%lld\n",dp[w]/2);
	return 0;
}
