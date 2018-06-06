#include<cstdio>
const long long MOD=100;

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
	for(;;)
	{
		scanf("%d",&T);
		if(T==0)
			break;
		for(int cas=1;cas<=T;cas++)
		{
			long long n,ans;
			scanf("%I64d",&n);
			ans=(PowMod(2,n-1)+PowMod(4,n-1))%MOD;
			printf("Case %d: %I64d\n",cas,ans);
		}
		puts("");
	}
	return 0;
}
