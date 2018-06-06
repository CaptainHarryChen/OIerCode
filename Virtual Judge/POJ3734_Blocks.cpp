#include<cstdio>
const long long MOD=10007;

long long PowMod(long long a,long long b)
{
	long long ret=1;
	while(b)
	{
		if(b&1LL)
			ret=ret*a%MOD;
		a=a*a%MOD;
		b>>=1LL;
	}
	return ret;
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		long long n,ans;
		scanf("%lld",&n);
		ans=(PowMod(2,n-1)+PowMod(4,n-1))%MOD;
		printf("%lld\n",ans);
	}
	return 0;
}
