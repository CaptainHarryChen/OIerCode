#include<cstdio>
#include<algorithm>
using namespace std;
const long long MOD=20101009LL,MAXN=10000005LL;
long long sum_mu[MAXN],prime[MAXN/3LL],pcnt;
bool noprime[MAXN];

void init_mu(int);
long long solve(long long,long long);
long long f(long long,long long);
long long sum(long long,long long);

int main()
{
	long long n,m;
	scanf("%lld%lld",&n,&m);
	init_mu(min(n,m));
	printf("%lld\n",solve(n,m));
	return 0;
}

void init_mu(int N)
{
	noprime[1]=1;
	sum_mu[1]=1LL;
	for(long long i=2LL;i<=N;i++)
	{
		if(!noprime[i])
		{
			prime[++pcnt]=i;
			sum_mu[i]=-1LL;
		}
		for(long long j=1;j<=pcnt&&i*prime[j]<=N;j++)
		{
			noprime[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				sum_mu[i*prime[j]]=0LL;
				break;
			}
			sum_mu[i*prime[j]]=-sum_mu[i];
		}
	}
	for(long long i=1LL;i<=N;i++)
		sum_mu[i]=(sum_mu[i-1]+((((i*i)%MOD)*sum_mu[i])%MOD))%MOD;
}

long long solve(long long n,long long m)
{
	long long ret=0LL,last;
	if(n>m)
		swap(n,m);
	for(long long d=1LL;d<=n;d=last+1)
	{
		last=min(n/(n/d),m/(m/d));
		ret=(ret+((sum(d,last)*f(n/d,m/d))%MOD))%MOD;
	}
	return ret;
}

long long f(long long x,long long y)
{
	if(x>y)
		swap(x,y);
	long long ret=0LL,last,tmp;
	for(long long k=1LL;k<=x;k=last+1LL)
	{
		last=min(x/(x/k),y/(y/k));
		tmp=(((((x/k)*(x/k+1LL))>>1LL)%MOD)
		*((((y/k)*(y/k+1LL))>>1LL)%MOD))%MOD;
		ret=(ret+(((sum_mu[last]-sum_mu[k-1]+MOD)%MOD)*tmp)%MOD)%MOD;
	}
	return ret;
}

long long sum(long long a,long long b)
{
	long long ret;
	ret=(((a+b)*(b-a+1LL))>>1LL)%MOD;
	return ret;
}
