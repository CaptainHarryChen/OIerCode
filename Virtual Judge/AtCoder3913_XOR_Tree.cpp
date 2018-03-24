#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int dp[1<<16],V[MAXN],cnt[16];

int DP(int s)
{
	if(s==0)
		return 0;
	if(dp[s]!=-1)
		return dp[s];
	dp[s]=0x3FFFFFFF;
	for(int i=1;i<16;i++)
		if(s&(1<<i))
			for(int j=1;j<16;j++)
				if(s&(1<<j))
				{
					int ns=s^(1<<i)^(1<<j)^(1<<(i^j));
					if(__builtin_popcount(ns)<__builtin_popcount(s))
						dp[s]=min(dp[s],DP(ns)+1+(((1<<(i^j))&s)==(1<<(i^j))));
				}
	return dp[s];
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1,x,y,a;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&a);
		V[x]^=a;
		V[y]^=a;
	}
	for(int i=0;i<n;i++)
		if(V[i])
			cnt[V[i]]++;
	int ans=0,st=0;
	for(int i=0;i<16;i++)
	{
		ans+=cnt[i]/2;
		st^=(cnt[i]&1)<<i;
	}
	memset(dp,-1,sizeof dp);
	ans+=DP(st);
	printf("%d\n",ans);
	
	return 0;
}
