#include<cstdio>
#include<cstring>
#define min(a,b) (a>b?b:a)
#define MAXN 10005
#define MAXM 105
#define MOD 1000000007LL
long long QPower(long long x,long long y)
{
	long long ret=1;
	for(;y;y>>=1,x=(x*x)%MOD)
		if(y&1)
			ret=(ret*x)%MOD;
	return ret;
}
long long fac[MAXN],inv[MAXN],dp[MAXN],FF[MAXN][MAXM];
int a[MAXN];
long long C(long long a,long long b)
{return fac[b]*inv[a]%MOD*inv[b-a]%MOD;}
long long F(long long a,long long b)
{
	if(a==1||b==0)return 1;
	if(~FF[a][b])return FF[a][b];
	long long ret=0;
	for(int t=1;t<=min(a,b);t++)
		ret=(ret+F(t,b-t)*C(t,a)%MOD)%MOD;
	return FF[a][b]=ret;
}
int main()
{
	int i,j,k;
	for(fac[0]=1,i=1;i<MAXN;i++)
		fac[i]=fac[i-1]*i%MOD;
	for(i=0;i<MAXN;i++)
		inv[i]=QPower(fac[i],MOD-2);
	int n,cas;
	memset(FF,-1,sizeof FF);
	for(cas=1;~scanf("%d",&n);cas++)
	{
		for(i=1;i<=n;i++)
			scanf("%d",&a[i]);
		memset(dp,0,sizeof dp);
		dp[0]=1;
		int sum=0;
		for(i=1;i<=n;sum+=a[i],i++)
			for(j=sum;j>=0;j--)
				for(k=1;k<=a[i];k++)
					dp[j+k]=(dp[j+k]+dp[j]*F(j+1,k)%MOD)%MOD;
		int ans=0;
		for(i=1;i<=sum;i++)
			ans=(ans+dp[i])%MOD;
		printf("Case %d: %d\n",cas,ans);
	}
	return 0;
}
