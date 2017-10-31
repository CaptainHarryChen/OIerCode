#include<cstdio>
#include<cstring>
const int MAXN=1005;
const long long MOD=1000000007LL,INV=500000004LL;
long long dp[MAXN][MAXN],t1[MAXN],t2[MAXN];
int main()
{
	int T,n,d;
	long long pow2;
	scanf("%d",&T);
	for(int Case=1;Case<=T;Case++)
	{
		memset(dp,0,sizeof dp);
		memset(t1,0,sizeof t1);
		memset(t2,0,sizeof t2);
		scanf("%d",&n);
		for(int i=1;i<n;i++)
		{
			scanf("%d",&d);
			if(i==1)
			{
				dp[i][1]=1LL;
				t1[i]=INV;
				t2[i]=INV;
				continue;
			}
			pow2=INV;
			for(int j=1;j<=i;j++)
			{
				if(d)
					dp[i][j]=dp[i-1][j-1];
				else
				{
					dp[i][j]=t1[i-1]%MOD;
					if(j==1)
						dp[i][j]=(dp[i][j]+t2[i-1])%MOD;
				}
				t1[i]=(t1[i]+(dp[i][j]*pow2)%MOD)%MOD;
				t2[i]=(t2[i]+(dp[i][j]*pow2)%MOD)%MOD;
				pow2=(pow2*INV)%MOD;
				t1[i-1]=((t1[i-1]*2LL)%MOD-dp[i-1][j]+MOD)%MOD;
			}
		}
		scanf("%d",&d);
		long long ans=0LL;
		pow2=INV;
		for(int i=1;i<=n;i++,pow2=(pow2*INV)%MOD)
			ans=(ans+(dp[n-1][i]*pow2)%MOD)%MOD;
		printf("Case #%d: %I64d\n",Case,ans);
	}
	return 0;
}
