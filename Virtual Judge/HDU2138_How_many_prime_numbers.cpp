#include<cstdio>
#include<cstdlib>
const int TEST=20;

long long mod_pow(long long a,long long b,long long p)
{
	long long ret=1LL;
	while(b)
	{
		if(b&1LL)
			ret=(ret*a)%p;
		a=(a*a)%p;
		b>>=1LL;
	}
	return ret;
}
bool MRTest(long long d,long long n)
{
	long long a=(1LL*rand()*rand())%(n-4LL)+2LL;
	long long x=mod_pow(a,d,n);
	if(x==1LL||x==n-1LL)
		return true;
	while(d<n-1LL)
	{
		x=(x*x)%n;
		d<<=1LL;
		if(x==n-1LL)return true;
	}
	return false;
}
bool isprime(long long n)
{
	if(n<=1LL||n==4LL)return false;
	if(n<=3LL)return true;
	long long d=n-1LL;
	while((d&1LL)==0LL)d>>=1LL;
	for(int i=1;i<=TEST;i++)
		if(!MRTest(d,n))
			return false;
	return true;
}

int main()
{
	int n,res;
	long long a;
	while(~scanf("%d",&n))
	{
		res=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%I64d",&a);
			res+=isprime(a);
		}
		printf("%d\n",res);
	}
	return 0;
}
