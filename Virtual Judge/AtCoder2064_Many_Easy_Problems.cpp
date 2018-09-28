#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const long long MAXN=1000005,MOD=924844033,ROOT=5;

long long PowMod(long long a,long long b)
{
	long long res=1;
	while(b)
	{
		if(b&1)
			res=1LL*res*a%MOD;
		a=1LL*a*a%MOD;
		b>>=1;
	}
	return res;
}

long long fac[MAXN],ifac[MAXN];
void InitFac()
{
	fac[0]=1;
	for(long long i=1;i<MAXN;i++)
		fac[i]=1LL*fac[i-1]*i%MOD;
	ifac[MAXN-1]=PowMod(fac[MAXN-1],MOD-2);
	for(long long i=MAXN-2;i>=0;i--)
		ifac[i]=1LL*ifac[i+1]*(i+1)%MOD;
}

void NTT(long long A[],long long n,long long mode)
{
	for(long long i=0,j=0;i<n;i++)
	{
		if(i<j)
			swap(A[i],A[j]);
		long long k=n>>1;
		while(j&k)
		{
			j^=k;
			k>>=1;
		}
		j^=k;
	}
	for(long long i=1;i<n;i<<=1)
	{
		long long w1=PowMod(ROOT,(MOD-1)/(i<<1)),w=1;
		if(mode==-1)
			w1=PowMod(w1,MOD-2);
		for(long long j=0;j<i;j++,w=(1LL*w*w1)%MOD)
            for(long long l=j,r=l+i;l<n;l+=(i<<1),r=l+i)
            {
                long long temp=(1LL*A[r]*w)%MOD;
                A[r]=(A[l]-temp+MOD)%MOD;
                A[l]=(A[l]+temp)%MOD;
            }
	}
	if(mode==-1)
	{
		long long inv=PowMod(n,MOD-2);
		for(long long i=0;i<n;i++)
			A[i]=1LL*A[i]*inv%MOD;
	}
}

long long N;
vector<long long> adj[MAXN];
long long cnt[MAXN],siz[MAXN];
long long A[MAXN],B[MAXN],ans[MAXN];

void dfs(long long u,long long f=0)
{
	siz[u]=1;
	for(auto v:adj[u])
	{
		if(v==f)
			continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
	cnt[siz[u]]++;
	cnt[N-siz[u]]++;
}

int main()
{
	InitFac();
	scanf("%lld",&N);
	for(long long i=1;i<N;i++)
	{
		long long u,v;
		scanf("%lld%lld",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	dfs(1);
	cnt[N]=-N;
	for(long long i=0;i<=N;i++)
		A[i]=-1LL*cnt[i]*fac[i]%MOD;
	for(long long i=0;i<=N;i++)
		B[i]=ifac[N-i];
	long long len=1;
	while(len<=N*2)
		len<<=1;
	NTT(A,len,1);
	NTT(B,len,1);
	for(long long i=0;i<=len;i++)
		A[i]=1LL*A[i]*B[i]%MOD;
	NTT(A,len,-1);
	for(long long i=1;i<=N;i++)
		ans[i]=(1LL*A[i+N]*ifac[i]%MOD+MOD)%MOD;
	for(long long i=1;i<=N;i++)
		printf("%lld\n",ans[i]);
	
	return 0;
}
