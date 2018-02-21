#include<cstdio>
const int MAXN=4641588,MOD=1000000007,MAXHASH=100000;

namespace Hash
{
	struct Node
	{
		long long id;
		int val;
		Node *nxt;
	}*adj[MAXHASH+10],node[MAXHASH+10],*ncnt=node;
	void add(long long pos,int val)
	{
		ncnt->id=pos;
		ncnt->val=val;
		ncnt->nxt=adj[pos%MAXHASH];
		adj[pos%MAXHASH]=ncnt;
		ncnt++;
	}
	int get(long long pos)
	{
		for(Node *p=adj[pos%MAXHASH];p;p=p->nxt)
			if(p->id==pos)
				return p->val;
		return -1;
	}
};

int preh[MAXN];
void init_h()
{
	static int phi[MAXN],pr[MAXN],pcnt=0;
	static bool npr[MAXN]={0};
	phi[1]=1;
	for(int i=2;i<MAXN;i++)
	{
		if(!npr[i])
		{
			pr[++pcnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=pcnt&&1LL*pr[j]*i<MAXN;j++)
		{
			npr[i*pr[j]]=true;
			if(i%pr[j]==0)
			{
				phi[i*pr[j]]=phi[i]*pr[j];
				break;
			}
			phi[i*pr[j]]=phi[i]*(pr[j]-1);
		}
	}
	preh[0]=0;
	for(int i=1;i<MAXN;i++)
		preh[i]=(preh[i-1]+(((1LL*i*i)%MOD)*phi[i])%MOD)%MOD;
}

int Sum(long long a,long long b)
{
	long long s1=a+b,s2=b-a+1;
	if(s1%2LL==0)s1/=2LL;
	else s2/=2LL;
	s1%=MOD;s2%=MOD;
	return (s1*s2)%MOD;
}
int Sum_pow2(long long a,long long b)
{
	a--;
	a%=MOD;b%=MOD;
	int s1=((((a*(a+1))%MOD*(2LL*a+1))%MOD)*166666668LL)%MOD;
	int s2=((((b*(b+1))%MOD*(2LL*b+1))%MOD)*166666668LL)%MOD;
	return (s2-s1+MOD)%MOD;
}
int Sum_pow3(long long n)
{
	int s=Sum(1,n);
	s=(1LL*s*s)%MOD;
	return s;
}

int h(long long n)
{
	if(n<MAXN)
		return preh[n];
	int t=Hash::get(n);
	if(t!=-1)
		return t;
	int ret=0;
	for(long long i=2,nxt=2;i<=n;i=nxt+1)
	{
		nxt=n/(n/i);
		ret=(ret+(1LL*Sum_pow2(i,nxt)*h(n/i))%MOD)%MOD;
	}
	ret=((Sum_pow3(n)-ret)%MOD+MOD)%MOD;
	Hash::add(n,ret);
	return ret;
}

int main()
{
	init_h();
	long long N;
	scanf("%lld",&N);
	int ans=0;
	for(long long i=1,nxt=1;i<=N;i=nxt+1)
	{
		nxt=N/(N/i);
		ans=(ans+(1LL*Sum(i,nxt)*h(N/i))%MOD)%MOD;
	}
	printf("%d\n",ans);
	return 0;
}
