#include<cstdio>
const int MAXN=1000005;
const long long MOD=998244353LL;

long long pow_mod(long long a,long long b)
{
	long long res=1LL;
	while(b)
	{
		if(b&1LL)
			res=(res*a)%MOD;
		a=(a*a)%MOD;
		b>>=1LL;
	}
	return res;
}
long long inv(long long x)
{return pow_mod(x,MOD-2);}

long long fac[MAXN],infac[MAXN],npow[MAXN];

void prepare(int n)
{
	fac[0]=1LL;
	for(int i=1;i<=n;i++)
		fac[i]=(fac[i-1]*i)%MOD;
	infac[n]=inv(fac[n]);
	for(int i=n-1;i>=0;i--)
		infac[i]=(infac[i+1]*(i+1))%MOD;
	npow[0]=1LL;
	for(int i=1;i<=n;i++)
		npow[i]=(npow[i-1]*(n-1))%MOD;
}
long long C(long long n,long long m)
{return fac[n]*infac[n-m]%MOD*infac[m]%MOD;}
long long sqr_mod(long long x)
{return x*x%MOD;}

int main()
{
	int n;
	scanf("%d",&n);
	prepare(n);
	long long ans=0LL,p;
	p=2LL*(n-1)%MOD*inv(n)%MOD;
	for(int d=0;d<=n-2;d++)
		ans=(ans+C(n-2,d)*sqr_mod(d+1)%MOD*npow[n-2-d]%MOD)%MOD;
	ans=(ans+MOD-sqr_mod(p)*pow_mod(n,n-2)%MOD)%MOD;
	printf("%lld\n",ans);
	return 0;
}
