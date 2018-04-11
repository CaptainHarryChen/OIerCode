#include<cstdio>

long long pow_mod(long long a,long long b,long long p)
{
	long long res=1;
	while(b)
	{
		if(b&1LL)
			res=(res*a)%p;
		b>>=1LL;
		a=(a*a)%p;
	}
	return res;
}
void exgcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0)
	{
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=(a/b)*x;
}
long long inv(long long a,long long p)
{
	long long i,t;
	exgcd(a,p,i,t);
	i=(i%p+p)%p;
	return i;
}

long long Fac(long long N,long long p,long long pk)
{
	if(N==0)
		return 1;
	long long ans=1;
	if(N>=pk)
	{
		for(long long i=1;i<pk;i++)
			if(i%p)
				ans=(ans*i)%pk;
		ans=pow_mod(ans,N/pk,pk);
	}
	for(long long i=1;i<=N%pk;i++)
		if(i%p)
			ans=(ans*i)%pk;
	ans=(ans*Fac(N/p,p,pk))%pk;
	return ans;
}
long long C(long long N,long long R,long long p,long long pk)
{
	if(R==0)
		return 1;
	long long a=Fac(N,p,pk),b=Fac(N-R,p,pk),c=Fac(R,p,pk),k=0,ans;
	for(long long i=N;i;i/=p)
		k+=i/p;
	for(long long i=N-R;i;i/=p)
		k-=i/p;
	for(long long i=R;i;i/=p)
		k-=i/p;
	ans=a*inv(b,pk)%pk*inv(c,pk)%pk*pow_mod(p,k,pk)%pk;
	return ans;
}
long long C(long long N,long long R,long long M)
{
	if(N<R)
		return 0;
	long long ans=0,m=M,temp;
	for(long long p=2,pk;p*p<=m;p++)
		if(m%p==0)
		{
			pk=1;
			while(m%p==0)
				m/=p,pk*=p;
			temp=C(N,R,p,pk);
			ans=(ans+temp*(M/pk)%M*inv(M/pk,pk)%M)%M;
		}
	if(m!=1)
	{
		temp=C(N,R,m,m);
		ans=(ans+temp*(M/m)%M*inv(M/m,m)%M)%M;
	}
	return ans;
}

int main()
{
	int T;
	scanf("%d",&T);
	long long N,K,M;
	while(T--)
	{
		scanf("%lld%lld%lld",&N,&K,&M);
		long long a=(N+K-1)/K,b=(K-N%K)%K;
		printf("%lld %lld\n",a,C(a+b-1,a-1,M));
	}
	return 0;
}
