#include<cstdio>  
using namespace std;
const int MAXN=23,MAXS=1<<20;
int n,m;
int prefer[MAXN];
int dp[MAXS];
int main()
{
	scanf("%d%d",&n,&m);
	int maxs=1<<m;
	for(int i=1,k;i<=n;i++)
	{
		scanf("%d",&k);
		for(int j=1,x;j<=k;j++)
		{
			scanf("%d",&x);
			prefer[i]+=(1<<(x-1));
		}
	}
	dp[0]=1;
	for(int s=1,k;s<maxs;s++)
	{
		k=__builtin_popcount(s);
		for(unsigned int i=1;i<0x7FFFFFFF;i<<=1U)
			if(prefer[k]&i)
				dp[s]+=dp[s^i];
	}
	int ans=0;
	for(int s=0;s<maxs;s++)
		if(__builtin_popcount(s)==n)
			ans+=dp[s];
	printf("%d\n",ans);
	return 0;
}
