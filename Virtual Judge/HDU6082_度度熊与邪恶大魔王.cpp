#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXM=1005,MAXA=1005,MAXB=12;
long long dp[MAXB][MAXA];
int a[MAXN],b[MAXN],k[MAXM],p[MAXM];
int main()
{
	int n,m,maxb,maxp;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		maxb=maxp=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",a+i,b+i);
			maxb=max(maxb,b[i]);
		}
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",k+i,p+i);
			maxp=max(maxp,p[i]);
		}
		if(maxb>=maxp)
		{
			printf("-1\n");
			continue;
		}
		memset(dp,0x3F,sizeof dp);
		for(int i=0;i<MAXB;i++)
			for(int j=0;j<MAXA;j++)
				for(int o=1;o<=m;o++)
				{
					if(p[o]<=i)continue;
					if(p[o]-i>=j)
						dp[i][j]=min(dp[i][j],1LL*k[o]);
					else
						dp[i][j]=min(dp[i][j],dp[i][j-p[o]+i]+1LL*k[o]);
				}
		long long ans=0;
		for(int i=1;i<=n;i++)
			ans+=dp[b[i]][a[i]];
		printf("%I64d\n",ans);
	}
	return 0;
}
