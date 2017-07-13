#include<cstdio>
const int MAXN=100005,MOD=1000000007;
int mu[MAXN],prime[MAXN/3],pcnt;
bool nprime[MAXN];
int fac[MAXN],inv[MAXN];
int mod_pow(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=(1LL*ret*a)%MOD;
		b>>=1;
		a=(1LL*a*a)%MOD;
	}
	return ret;
}
void Init()
{
	mu[1]=1;
	nprime[1]=1;
	for(long long i=2;i<MAXN;i++)
	{
		if(!nprime[i])
		{
			prime[++pcnt]=i;
			mu[i]=-1;
		}
		for(long long j=1;j<=pcnt&&i*prime[j]<MAXN;j++)
		{
			nprime[i*prime[j]]=1;
			if(i%prime[j]==0)
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	fac[0]=1;
	inv[0]=1;
	for(int i=1;i<MAXN;i++)
	{
		fac[i]=(1LL*fac[i-1]*i)%MOD;
		inv[i]=mod_pow(fac[i],MOD-2);
	}
}
int C(int n,int m)
{
	if(m>n)
		return 0;
	int ret=1;
	ret=(1LL*fac[n]*inv[m])%MOD;
	ret=(1LL*ret*inv[n-m])%MOD;
	return ret;
}
int solve(int n,int f)
{
	int ans=0;
	for(int i=1;1LL*i*i<=1LL*n;i++)
		if(n%i==0)
		{
			ans=(1LL*ans+1LL*mu[i]*C(n/i-1,f-1)+1LL*MOD)%MOD;
			if(1LL*i*i!=1LL*n)
				ans=(1LL*ans+1LL*mu[n/i]*C(i-1,f-1)+1LL*MOD)%MOD;
		}
	return ans;
}
int main()
{
	Init();
	int T,n,f;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&f);
		printf("%d\n",solve(n,f));
	}
	return 0;
}
