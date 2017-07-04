#include<cstdio>
#include<iostream>
#include<algorithm>
#define MAXN 50005
long long W[MAXN],S[MAXN],Sort[MAXN],n;
bool cmp(long long a,long long b)
{return (W[a]+S[a])<(W[b]+S[b]);}
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld%lld",&W[i],&S[i]);
		Sort[i]=i;
	}
	std::sort(Sort+1,Sort+n+1,cmp);
	long long sum=0,ans=-9223372036854775807LL;
	for(long long i=1;i<=n;i++)
	{
		ans=std::max(ans,sum-S[Sort[i]]);
		sum+=W[Sort[i]];
	}
	printf("%lld\n",ans);
	return 0;
}
