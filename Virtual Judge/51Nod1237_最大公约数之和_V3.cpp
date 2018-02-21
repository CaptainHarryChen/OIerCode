#include<cstdio>
const long long MAXN=4641588,MOD=1000000007,MAXHASH=100000;

long long val[MAXHASH+5],id[MAXHASH+5];
int nxt[MAXHASH+5],adj[MAXHASH+5],ncnt;
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

int sumphi[MAXN+10];

void init_sumphi()
{
	static int phi[MAXN],prime[MAXN],pcnt=0;
	static bool npr[MAXN]={false};
	phi[1]=1;npr[1]=true;
	for(long long i=2;i<MAXN;i++)
	{
		if(!npr[i])
		{
			prime[++pcnt]=i;
			phi[i]=i-1;
		}
		for(long long j=1;j<=pcnt&&1LL*prime[j]*i<MAXN;j++)
		{
			npr[i*prime[j]]=true;
			if(i%prime[j]==0)
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	sumphi[0]=0;
	for(long long i=1;i<MAXN;i++)
		sumphi[i]=(sumphi[i-1]+phi[i])%MOD;
}

long long get_sumphi(long long n)
{
	if(n<MAXN)
		return sumphi[n];
	long long t=get(n);
	if(t!=-1)
		return t;
	long long res=0,nxt=0;
	for(long long k=2;k<=n;k=nxt+1LL)
	{
		nxt=n/(n/k);
		res=(res+((nxt-k+1LL)%MOD)*(get_sumphi(n/k))%MOD)%MOD;
	}
	if(n%2LL==0LL)res=(((n/2LL)%MOD)*((n+1LL)%MOD)%MOD-res+MOD)%MOD;
	else res=((n%MOD)*(((n+1LL)/2LL)%MOD)%MOD-res+MOD)%MOD;
	add(n,res);
	return res;
}

long long sum(long long a,long long b)
{
	long long c=a+b,d=b-a+1;
	if(c%2LL==0LL)
		c/=2LL;
	else
		d/=2LL;
	c%=MOD;d%=MOD;
	return (c*d)%MOD;
}

int main()
{
	init_sumphi();
	long long N=0,g=0,ans=0;
	scanf("%lld",&N);
	for(long long i=1,nxt=0;i<=N;i=nxt+1)
	{
		nxt=N/(N/i);
		g=(g+(sum(i,nxt)*get_sumphi(N/i))%MOD)%MOD;
	}
	ans=((2*g)%MOD-sum(1,N)+MOD)%MOD;
	printf("%lld\n",ans);
	return 0;
}
