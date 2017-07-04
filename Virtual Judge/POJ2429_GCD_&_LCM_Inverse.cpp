#include<cstdio>
#include<cstdlib>
#include<map>
#include<vector>
using namespace std;
#define MAX_PRIME 200000LL
#define MAX_FACTORIZE 10000LL
#define MAX_POLLARD_RHO_SEED 200LL
#define MILLER_RABIN_TIMES 20
typedef map<long long,int> Pfactors;
typedef vector<long long> Factors;
bool isprime[MAX_PRIME];
void Make_prime_list()
{
	for(long long i=2LL;i<MAX_PRIME;i++)
		if(!isprime[i])
			for(long long j=i*i;j<MAX_PRIME;j+=i)
				isprime[j]=1;
}
long long mod_mul(long long a,long long b,long long p)
{
	long long ret=0LL;
	while(b)
	{
		if(b&1LL)
			ret=(ret+a)%p;
		a=(a+a)%p;
		b>>=1LL;
	}
	return ret;
}
long long mod_pow(long long a,long long b,long long p)
{
	long long ret=1LL;
	while(b)
	{
		if(b&1LL)
			ret=mod_mul(ret,a,p);
		a=mod_mul(a,a,p);
		b>>=1LL;
	}
	return ret;
}
long long gcd(long long a,long long b)
{
	long long tmp;
	while(b)
	{
		tmp=a;
		a=b;
		b=tmp%b;
	}
	return a;
}
bool miller_rabin(long long n)
{
	long long q=n-1LL;
	int k=0;
	while((q&1LL)==0LL)
	{
		k++;
		q>>=1LL;
	}
	for(int times=1;times<=MILLER_RABIN_TIMES;times++)
	{
		long long a=rand()*rand()%(n-1LL)+1LL;
		long long tmp=mod_pow(a,q,n);
		if(tmp==1)
			continue;
		bool success=0;
		for(int i=1;i<=k;i++)
		{
			if(tmp==n-1LL)
			{
				success=1;
				break;
			}
			tmp=mod_mul(tmp,tmp,n);
		}
		if(success)
			continue;
		return 0;
	}
	return 1;
}
bool isPrime(long long n)
{
	if(n<MAX_PRIME)
		return !isprime[n];
	return miller_rabin(n);
}
long long pollard_rho(long long n)
{
	long long x1,x2;
	for(int seed=1;seed<=MAX_POLLARD_RHO_SEED;seed++)
	{
		x2=2LL;
		x1=x2;
		while(1)
		{
			x1=(mod_pow(x1,2LL,n)+seed)%n;
			long long d=gcd((x2-x1+n)%n,n);
			if(1LL<d&&d<n)
				return d;
			x2=(mod_pow(x2,2LL,n)+seed)%n;
			x2=(mod_pow(x2,2LL,n)+seed)%n;
			if(x2==x1)
				break;
		}
	}
	return n;
}
void Factorize(Pfactors &res,long long n)
{
	if(isPrime(n))
	{
		res[n]++;
		return;
	}
	if(n<=MAX_FACTORIZE)
	{
		for(int i=2;i<=n;i++)
			if(!isprime[i]&&n%i==0)
				while(n%i==0)
				{
					res[i]++;
					n/=i;
				}
		return;
	}
	long long p=pollard_rho(n);
	Factorize(res,p);
	Factorize(res,n/p);
}
void enum_solve(const Factors &fa,long long n,long long &ansx,long long &ansy,int step=0,long long pro=1LL)
{
	if(step>=(int)fa.size())
	{
		long long q=n/pro;
		if(pro+q<ansx+ansy)
		{
			ansx=min(pro,q);
			ansy=max(pro,q);
		}
		return;
	}
	enum_solve(fa,n,ansx,ansy,step+1,pro*fa[step]);
	enum_solve(fa,n,ansx,ansy,step+1,pro);
}
int main()
{	
	long long g,l;
	Pfactors t;
	Factors fa;
	Make_prime_list();
	while(~scanf("%lld%lld",&g,&l))
	{
		long long temp,x;
		temp=l/g;
		t.clear();
		fa.clear();
		Factorize(t,temp);
		for(Pfactors::iterator i=t.begin();i!=t.end();i++)
		{
			x=1;
			for(int j=1;j<=i->second;j++)
				x*=i->first;
			fa.push_back(x);
		}
		long long ansx=0LL,ansy=0x7FFFFFFFFFFFFFFFLL;
		enum_solve(fa,temp,ansx,ansy);
		ansx*=g;ansy*=g;
		printf("%lld %lld\n",ansx,ansy);
	}
	return 0;
}
