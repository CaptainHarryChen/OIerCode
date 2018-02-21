#include<cstdio>
const long long MAXN=1000000,MOD=1000000007,MAXHASH=100000;

long long sumu[MAXN+10];
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

long long pow_mod(long long a,long long b)
{
	long long res=1;
	while(b)
	{
		if(b&1LL)
			res=(a*res)%MOD;
		b>>=1LL;
		a=(a*a)%MOD;
	}
	return res;
}

long long val[MAXHASH+5],id[MAXHASH+5];
long long nxt[MAXHASH+5],adj[MAXHASH+5],ncnt;
void add(long long pos,long long v)
{
	long long hash=pos%MAXHASH;
	ncnt++;
	id[ncnt]=pos;
	val[ncnt]=v;
	nxt[ncnt]=adj[hash];
	adj[hash]=ncnt;
}
long long get(long long pos)
{
	long long hash=pos%MAXHASH;
	for(long long it=adj[hash];it;it=nxt[it])
		if(id[it]==pos)
			return val[it];
	return -1;
}

long long solve(long long n)
{
	if(n<MAXN)
		return sumu[n];
	long long t=get(n);
	if(t!=-1)
		return t;
	long long res=1,nxt=0;
	for(long long k=2;k<=n;)
	{
		nxt=n/(n/k);
		res-=(nxt-k+1)*solve(n/k);
		k=nxt+1;
	}
	add(n,res);
	return res;
}

long long inv;
long long C(long long n)
{
    long long s1=1;
	for(long long i=n-2;i<=n;i++)
		s1=(s1*i)%MOD;
	return (s1*inv)%MOD;
}

int main()
{
	init_sumu();
	inv=pow_mod(3,MOD-2);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		long long N,ans=0;
		scanf("%I64d",&N);
		for(long long i=1,k=1;i<=N;i=k+1)
		{
			k=N/(N/i);
			ans=((ans+(1LL*((C(k)-C(i-1)+MOD)%MOD)*solve(N/i))%MOD)%MOD+MOD)%MOD;
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
