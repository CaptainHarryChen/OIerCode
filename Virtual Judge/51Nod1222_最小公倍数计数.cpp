#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=10000005;
int mu[MAXN],prime[670000],pcnt;
bool nprime[MAXN];
void Init(long long N)
{
	nprime[1]=1;mu[1]=1;
	for(int i=2;i<=N;i++)
	{
		if(!nprime[i])
		{
			prime[++pcnt]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=pcnt&&i*prime[j]<=N;j++)
		{
			nprime[i*prime[j]]=1;
			if(i%prime[j]==0)
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<=N;i++)
		mu[i]+=mu[i-1];
}
long long f(long long x)
{
	long long ret=0;
	for(long long i=1LL;i*i*i<=x;i++)
	{
		for(long long j=i+1LL;i*j*j<=x;j++)
			ret+=(x/(i*j)-j)*6LL+3LL;
		ret+=(x/(i*i)-i)*3LL;
		ret++;
	}
	return ret;
}
long long solve(long long N)
{
	long long ret=0,last,t=sqrt(N);
 	for(long long d=1;d<=t;d=last+1)
	{
		last=min((long long)sqrt(N/(N/(d*d))),t);
		if(mu[last]-mu[d-1])
			ret+=1LL*f(N/(d*d))*(mu[last]-mu[d-1]);
	}
	return 1LL*(ret+N)/2LL;
}
int main()
{
	long long a,b;
	scanf("%lld%lld",&a,&b);
	Init(sqrt(max(a,b)));
	printf("%lld\n",solve(b)-solve(a-1));
	return 0;
}
