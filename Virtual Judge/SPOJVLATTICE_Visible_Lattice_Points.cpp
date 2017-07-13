#include<cstdio>
const long long MAXN=1000005LL;
long long mu[MAXN],prime[MAXN/3LL],pcnt;
long long sum[MAXN];
bool noprime[MAXN];
void init_mu()
{
    noprime[1]=1;
    mu[1]=1LL;
    for(long long i=2LL;i<MAXN;i++)
    {
        if(!noprime[i])
        {
            prime[++pcnt]=i;
            mu[i]=-1LL;
        }
        for(long long j=1;j<=pcnt&&i*prime[j]<MAXN;j++)
        {
            noprime[i*prime[j]]=1;
            if(i%prime[j]==0)
                break;
            mu[i*prime[j]]=-mu[i];
        }
    }
	for(long long i=1LL;i<MAXN;i++)
		sum[i]=sum[i-1]+mu[i];
}
int main()
{
	init_mu();
	int T,n,last;
	long long ans;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		ans=0LL;
		for(int i=1;i<=n;i=last+1)
		{
			last=n/(n/i);
			ans+=1LL*(n/i+1)*(n/i+1)*(n/i+1)*(sum[last]-sum[i-1]);
		}
		ans-=sum[n];
		printf("%lld\n",ans);
	}
	return 0;
}
