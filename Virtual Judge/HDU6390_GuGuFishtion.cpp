#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1000005;
int MOD=1000000007;

int PowMod(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=(1LL*ret*a)%MOD;
		a=(1LL*a*a)%MOD;
		b>>=1;
	}
	return ret;
}

bool npr[MAXN];
int prime[MAXN],pcnt;
int mu[MAXN],phi[MAXN],summu[MAXN];

void LinerSieve()
{
	mu[1]=1;
	phi[1]=1;
	npr[1]=true;
	pcnt=0;
	for(int i=2;i<MAXN;i++)
	{
		if(!npr[i])
		{
			prime[++pcnt]=i;
			phi[i]=i-1;
			mu[i]=-1;
		}
		for(int j=1;j<=pcnt&&1LL*prime[j]*i<MAXN;j++)
		{
			npr[prime[j]*i]=true;
			if(i%prime[j]==0)
			{
				mu[i*prime[j]]=0;
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			mu[i*prime[j]]=-mu[i];
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	for(int i=1;i<MAXN;i++)
		summu[i]=summu[i-1]+mu[i];
}

int fac[MAXN],ifac[MAXN],inv[MAXN];

void InitInv(int N)
{
	fac[0]=1;
	for(int i=1;i<N;i++)
		fac[i]=(1LL*fac[i-1]*i)%MOD;
	ifac[N-1]=PowMod(fac[N-1],MOD-2);
	for(int i=N-2;i>=0;i--)
		ifac[i]=(1LL*ifac[i+1]*(i+1))%MOD;
	for(int i=1;i<N;i++)
		inv[i]=(1LL*ifac[i]*fac[i-1])%MOD;
}

int F(int m,int n)
{
	int ret=0;
	for(int d=1,nxt;d<=min(m,n);d=nxt+1)
	{
		nxt=min(m/(m/d),n/(n/d));
		ret=(ret+1LL*(m/d)*(n/d)%MOD*(summu[nxt]-summu[d-1])%MOD+MOD)%MOD;
	}
	return ret;
}

int main()
{
	LinerSieve();
	int T,m,n;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&m,&n,&MOD);
		InitInv(max(m,n));
		int ans=0;
		for(int g=1;g<=min(m,n);g++)
			ans=(ans+1LL*g*inv[phi[g]]%MOD*F(m/g,n/g)%MOD)%MOD;
		printf("%d\n",ans);
	}
	return 0;
}
