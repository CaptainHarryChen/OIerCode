#include<cstdio>
const int MAXN=200005,MAXA=2005,ZERO=2005,MOD=1000000007;

int powmod(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=(1LL*ret*a)%MOD;
		a=(1LL*a*a)%MOD;
		b>>=1;
	}
	return ret;
}

int a[MAXN],b[MAXN];
int f[MAXA*2][MAXA*2];
int fac[MAXA*4],ifac[MAXA*4];

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		f[ZERO-a[i]][ZERO-b[i]]++;
	}
	for(int i=1;i<MAXA*2;i++)
		for(int j=1;j<MAXA*2;j++)
			f[i][j]=((f[i][j]+f[i-1][j])%MOD+f[i][j-1])%MOD;
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=(ans+f[a[i]+ZERO][b[i]+ZERO])%MOD;
	fac[0]=1;
	for(int i=1;i<MAXA*4;i++)
		fac[i]=(1LL*fac[i-1]*i)%MOD;
	ifac[MAXA*4-1]=powmod(fac[MAXA*4-1],MOD-2);
	for(int i=MAXA*4-2;i>=0;i--)
		ifac[i]=(1LL*ifac[i+1]*(i+1))%MOD;
	
	for(int i=1;i<=n;i++)
		ans=(ans-1LL*fac[(a[i]+b[i])*2]*ifac[b[i]*2]%MOD*ifac[a[i]*2]%MOD)%MOD;
	ans=(ans+MOD)%MOD;
	ans=(1LL*(MOD+1)/2*ans)%MOD;
	printf("%d\n",ans);
	
	return 0;
}
