#include<cstdio>
#include<map>
using namespace std;
const long long MAXN=5000000;

long long sumu[MAXN+10];
map<long long,long long> S;

void init_sumu()
{
	static long long mu[MAXN],prime[MAXN],pcnt=0;
	static bool npr[MAXN]={false};
	mu[1]=1;npr[1]=true;
	for(long long i=2;i<MAXN;i++)
	{
		if(!npr[i])
		{
			prime[++pcnt]=i;
			mu[i]=-1;
		}
		for(long long j=1;j<=pcnt&&1LL*prime[j]*i<MAXN;j++)
		{
			npr[i*prime[j]]=true;
			if(i%prime[j]==0)
			{
				mu[i*prime[j]]=0;
				break;
			}
			mu[i*prime[j]]=-mu[i];
		}
	}
	sumu[0]=0;
	for(long long i=1;i<MAXN;i++)
		sumu[i]=sumu[i-1]+mu[i];
}

long long solve(long long n)
{
	if(n<MAXN)
		return sumu[n];
	if(S.count(n))
		return S[n];
	long long res=1,nxt=0;
	for(long long k=2;k<=n;)
	{
		nxt=n/(n/k);
		res-=(nxt-k+1)*solve(n/k);
		k=nxt+1;
	}
	S[n]=res;
	return res;
}

int main()
{
	init_sumu();
	long long a,b;
	scanf("%lld%lld",&a,&b);
	printf("%lld\n",solve(b)-solve(a-1));
	return 0;
}
