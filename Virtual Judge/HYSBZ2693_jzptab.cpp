#include<cstdio>
#include<algorithm>
using namespace std;
const long long MOD=100000009LL,MAXN=10000005LL;
long long mu[MAXN],prime[MAXN/3LL],pcnt;
long long sum[MAXN];
bool noprime[MAXN];

void init_mu();
long long solve(long long,long long);

int main()
{
    long long n,m,T;
	init_mu();
	scanf("%lld",&T);
    while(T--)
	{
		scanf("%lld%lld",&n,&m);
		printf("%lld\n",solve(n,m));
	}
    return 0;
}

void init_mu()
{
    noprime[1]=1;
    mu[1]=1LL;
	sum[1]=1LL;
    for(long long i=2LL;i<MAXN;i++)
    {
        if(!noprime[i])
        {
            prime[++pcnt]=i;
            mu[i]=-1LL;
			sum[i]=-i+1;
        }
        for(long long j=1;j<=pcnt&&i*prime[j]<MAXN;j++)
        {
            noprime[i*prime[j]]=1;
            if(i%prime[j]==0)
            {
				long long tmp=i;
				while(tmp%prime[j]==0)
					tmp/=prime[j];
				sum[i*prime[j]]=sum[tmp]*sum[prime[j]];
                mu[i*prime[j]]=0LL;
                break;
            }
			sum[i*prime[j]]=sum[i]*sum[prime[j]];
            mu[i*prime[j]]=-mu[i];
        }
    }
	for(long long i=1;i<MAXN;i++)
		sum[i]=(sum[i-1]+((sum[i]*i)%MOD)+MOD)%MOD;
}

long long solve(long long n,long long m)
{
    long long ret=0LL,last=0,tmp=0;
    if(n>m)
        swap(n,m);
    for(long long d=1LL;d<=n;d=last+1)
    {
        last=min(n/(n/d),m/(m/d));
        tmp=(((((n/d)*(n/d+1LL))>>1LL)%MOD)
        *((((m/d)*(m/d+1LL))>>1LL)%MOD))%MOD;
        ret=(ret+(((sum[last]-sum[d-1]+MOD)%MOD)*tmp)%MOD)%MOD;
    }
    return ret;
}
