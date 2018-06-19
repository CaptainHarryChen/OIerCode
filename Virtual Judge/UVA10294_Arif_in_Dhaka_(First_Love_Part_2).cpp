#include<cstdio>
const long long MAXN=55;

long long pri[MAXN],pcnt,phi[MAXN];
bool npr[MAXN];

void Sieve()
{
	npr[1]=1;
	phi[1]=1;
	for(long long i=2;i<MAXN;i++)
	{
		if(!npr[i])
		{
			pri[++pcnt]=i;
			phi[i]=i-1;
		}
		for(long long j=1;j<=pcnt&&i*pri[j]<MAXN;j++)
		{
			npr[i*pri[j]]=true;
			if(i%pri[j]==0)
			{
				phi[i*pri[j]]=phi[i]*pri[j];
				break;
			}
			phi[i*pri[j]]=phi[i]*(pri[j]-1);
		}
	}
}
long long Pow(long long a,long long b)
{
	long long ret=1;
	while(b)
	{
		if(b&1LL)
			ret=1LL*ret*a;
		a=a*a;
		b>>=1LL;
	}
	return ret;
}

int main()
{
	Sieve();
	long long ans;
	long long N,t;
	while(scanf("%lld%lld",&N,&t)!=EOF)
	{
		ans=0;
		for(long long d=1;d*d<=N;d++)
			if(N%d==0)
			{
				ans+=Pow(t,d)*phi[N/d];
				if(N/d!=d)
					ans+=Pow(t,N/d)*phi[d];
			}
		printf("%lld ",ans/N);
		if(N%2==0)
			ans+=Pow(t,N/2+1)*N/2+Pow(t,N/2)*N/2;
		else
			ans+=Pow(t,N/2+1)*N;
		ans/=2*N;
		printf("%lld\n",ans);
	}
	return 0;
}
