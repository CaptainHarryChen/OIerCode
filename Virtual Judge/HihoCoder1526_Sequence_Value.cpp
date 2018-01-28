#include<cstdio>
const int MAXN=100005,MOD=998244353;

int n;
int A[MAXN];
int dp[35][2];
int pow2[MAXN];

int main()
{
	int n,ans=0;
	scanf("%d",&n);
	pow2[0]=1;
	for(int i=1;i<=n;i++)
		pow2[i]=(pow2[i-1]*2LL)%MOD;
	for(int i=1;i<=n;i++)
		scanf("%d",A+i);
	for(int i=0;i<31;i++)
		dp[i][0]=1;
	for(int i=1;i<=n;i++)
	{
		if(A[i]!=0)
		{
			int k=30;
			while((A[i]&(1<<k))==0)
				k--;
			ans=(ans+1LL*dp[k][0]*pow2[n-i]%MOD)%MOD;
		}
		int add[35][2]={{0}};
		for(int j=0;j<31;j++)
		{
			add[j][0]=dp[j][(A[i]>>j)&1];
			add[j][1]=dp[j][((A[i]>>j)&1)^1];
		}
		for(int j=0;j<31;j++)
		{
			dp[j][0]=(dp[j][0]+add[j][0])%MOD;
			dp[j][1]=(dp[j][1]+add[j][1])%MOD;
		}
	}
	printf("%d\n",ans);
	return 0;
}
