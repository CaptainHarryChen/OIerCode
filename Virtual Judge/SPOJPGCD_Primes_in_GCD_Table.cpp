#include<cstdio>
#include<algorithm>
using namespace std;
const long long MAXN=10000005LL;
int mu[MAXN],prime[MAXN/3LL],pcnt;
long long sum[MAXN];
bool noprime[MAXN];
void init_mu()
{
    noprime[1]=1;
    mu[1]=1;
    for(int i=2;i<MAXN;i++)
    {
        if(!noprime[i])
        {
            prime[++pcnt]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=pcnt&&i*prime[j]<MAXN;j++)
        {
            noprime[i*prime[j]]=1;
            if(i%prime[j]==0)
                break;
            mu[i*prime[j]]=-mu[i];
        }
    }
	for(int i=1;i<=pcnt;i++)
		for(int j=prime[i];j<MAXN;j+=prime[i])
			sum[j]+=mu[j/prime[i]];
	for(int i=1;i<MAXN;i++)
		sum[i]+=sum[i-1];
}
int main()
{
	init_mu();
	int T,n,m,last;
	long long ans;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		if(n>m)
			swap(n,m);
		ans=0;
		for(int i=1;i<=n;i=last+1)
		{
			last=min(n/(n/i),m/(m/i));
			ans+=1LL*(n/i)*(m/i)*(sum[last]-sum[i-1]);
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
