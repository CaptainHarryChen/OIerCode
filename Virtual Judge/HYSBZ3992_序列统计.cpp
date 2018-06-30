#include<cstdio>
#include<algorithm>
using namespace std;
const long long MOD=1004535809,ROOT=3,MAXM=8005,MAXL=16400;

long long PowMod(long long a,long long b,long long p=MOD)
{
	long long ret=1;
	while(b)
	{
		if(b&1LL)
			ret=(1LL*ret*a)%p;
		b>>=1LL;
		a=(1LL*a*a)%p;
	}
	return ret;
}
void NTT(long long A[],long long n,long long mode)
{
	for(long long i=0,j=0;i<n;i++)
	{
		if(i<j)
			swap(A[i],A[j]);
		long long k=n>>1LL;
		while(k&&(k&j))
			j^=k,k>>=1LL;
		j^=k;
	}
	for(long long i=1;i<n;i<<=1LL)
		for(long long j=0;j<n;j+=(i<<1LL))
		{
			long long w1=PowMod(ROOT,(MOD-1)/(i<<1LL)),w=1;
			if(mode==-1)
				w1=PowMod(w1,MOD-2);
			for(long long l=j,r=j+i;l<j+i;l++,r++,w=(1LL*w*w1)%MOD)
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
			A[i]=(1LL*A[i]*inv)%MOD;
	}
}

void Mul(long long A[],long long len1,const long long B[],long long len2)
{
	static long long t[MAXL]={0};
	long long len=1;
	while(len<len1+len2-1)
		len<<=1LL;
	for(long long i=len1;i<len;i++)A[i]=0;
	for(long long i=0;i<len2;i++)t[i]=B[i];
	for(long long i=len2;i<len;i++)t[i]=0;
	NTT(A,len,1);
	NTT(t,len,1);
	for(long long i=0;i<len;i++)
		A[i]=(1LL*A[i]*t[i])%MOD;
	NTT(A,len,-1);
}

long long ans[MAXL];
long long pos[MAXL];

long long Solve(long long A[],long long M,long long N,long long x)
{
	static long long t[MAXL]={1};
	while(N)
	{
		if(N&1LL)
		{
			Mul(t,M,A,M);
			for(long long i=M;i<2LL*M;i++)
			{
				t[i-M]=(t[i-M]+t[i])%MOD;
				t[i]=0;
			}
			//N--;
		}
		Mul(A,M,A,M);
		for(long long i=M;i<2LL*M;i++)
		{
			A[i-M]=(A[i-M]+A[i])%MOD;
			A[i]=0;
		}
		N>>=1LL;
	}
	return t[pos[x]];
}

int main()
{
	long long N,M,x,S;
	scanf("%lld%lld%lld%lld",&N,&M,&x,&S);
	long long r=2;
	for(bool flag=false;!flag;r++)
	{
		flag=true;
		for(long long i=1;i*i<=M&&flag;i++)
			if((M-1)%i==0)
				if((PowMod(r,i,M)==1)||(PowMod(r,(M-1)/i,M)==1&&i!=1))
					flag=false;
	}
	r--;
	pos[1]=0;
	for(long long i=1,a=r;i<M-1;i++,a=(1LL*a*r)%M)
		pos[a]=i;
	for(long long i=1;i<=S;i++)
	{
		long long a;
		scanf("%lld",&a);
		if(a==0)continue;
		ans[pos[a]]++;
	}
	
	printf("%lld\n",Solve(ans,M-1,N,x));
	
	return 0;
}
