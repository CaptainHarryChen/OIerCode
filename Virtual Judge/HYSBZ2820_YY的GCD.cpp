#include<cstdio>
#include<algorithm>
using namespace std;
const long long MAXN=10000005;
long long prime[MAXN/3],pcnt;
long long mu[MAXN],sum[MAXN];
bool noprime[MAXN];
void Init()
{
	noprime[1]=1;
	mu[1]=1;
	for(long long i=2;i<MAXN;i++)
	{
		if(!noprime[i])
		{
			mu[i]=-1;
			prime[++pcnt]=i;
		}
		for(long long j=1;j<=pcnt&&i*prime[j]<MAXN;j++)
		{
			noprime[i*prime[j]]=1;
			if(i%prime[j]==0)
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(long long i=1;i<=pcnt;i++)
		for(long long j=prime[i];j<MAXN;j+=prime[i])
			sum[j]+=mu[j/prime[i]];
	for(long long i=1;i<MAXN;i++)
		sum[i]+=sum[i-1];
}
int main()
{
	Init();
	long long T,n,m,ans,last;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&m);
		if(n>m)
			swap(n,m);
		ans=0;
		for(long long i=1;i<=n;i=last+1)
		{
			last=min(n/(n/i),m/(m/i));
			ans+=(n/i)*(m/i)*(sum[last]-sum[i-1]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
