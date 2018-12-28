#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=305;

int n,m,M;
int C[MAXN][MAXN];
int cnt[MAXN],sum[MAXN],dp[MAXN][MAXN];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&n,&m,&M);
		C[0][0]=1;
		for(int i=1;i<=n;i++)
		{
			C[i][0]=1;
			for(int j=1;j<=i;j++)
				C[i][j]=(C[i-1][j]+C[i-1][j-1])%M;
		}
		memset(cnt,0,sizeof cnt);
		memset(sum,0,sizeof sum);
		for(int i=1,x;i<=m;i++)
		{
			scanf("%d%d",&x,&x);
			cnt[n-x+1]++;
		}
		bool flag=true;
		for(int i=1;i<=n&&flag;i++)
		{
			sum[i]=sum[i-1]+cnt[i];
			if(sum[i]>i)
				flag=false;
		}
		if(!flag)
		{
			puts("NO");
			continue;
		}
		memset(dp,0,sizeof dp);
		dp[0][0]=1;
		for(int i=1;i<=n;i++)
			for(int j=sum[i];j<=i;j++)
				for(int k=cnt[i];k<=j;k++)
					dp[i][j]=(dp[i][j]+1LL*dp[i-1][j-k]*C[n-m-j+k+sum[i-1]][k-cnt[i]]%M)%M;
		printf("YES %d\n",dp[n][n]);
	}
	return 0;
}
