#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 10000005
int prime[MAXN],tot,ind[MAXN];
bool not_prime[MAXN];
long long pmin[MAXN],sum[MAXN];
int main()
{
	for(int i=2;i<MAXN;i++)
	{
		if(!not_prime[i])
		{
			prime[++tot]=i;
			ind[i]=1;
			pmin[i]=i;
			sum[i]=1;
		}
		for(int j=1;j<=tot&&i*prime[j]<MAXN;j++)
		{
			not_prime[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				ind[i*prime[j]]=ind[i]+1;
				pmin[i*prime[j]]=pmin[i]*prime[j];
				int t=i/pmin[i];
				if(t==1)
					sum[i*prime[j]]=1;
				else
					sum[i*prime[j]]=(ind[t]==ind[i*prime[j]])?-sum[t]:0;
				break;
			}
			pmin[i*prime[j]]=prime[j];
			ind[i*prime[j]]=1;
			sum[i*prime[j]]=(ind[i]==1)?-sum[i]:0;
		}
	}
	for(int i=1;i<MAXN;i++)
		sum[i]+=sum[i-1];
	int cas,a,b;
	for(scanf("%d",&cas);cas;cas--)
	{
		scanf("%d%d",&a,&b);
		if(a>b)swap(a,b);
		int last=0;
		long long ans=0;
		for(int i=1;i<=a;i=last+1)
		{
			last=min(a/(a/i),b/(b/i));
			ans+=1LL*(a/i)*(b/i)*(sum[last]-sum[i-1]);
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
