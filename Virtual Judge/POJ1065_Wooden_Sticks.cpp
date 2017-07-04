#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 5005
pair<int,int>sti[MAXN];
int dp[MAXN];
int main()
{
	int T,n;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&sti[i].first,&sti[i].second);
		sort(sti+1,sti+n+1);
		sti[0].second=0x7FFFFFFF;
		memset(dp,0,sizeof dp);
		int ans=0;
		for(int i=1;i<=n;i++)
			for(int j=0;j<i;j++)
				if(sti[j].second>sti[i].second)
				{
					dp[i]=max(dp[i],dp[j]+1);
					ans=max(ans,dp[i]);
				}
		printf("%d\n",ans);
	}
	return 0;
}
