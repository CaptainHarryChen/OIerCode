#include<cstdio>
const int TEST_VAL[]={2,3,5,7,11,13,17,19,23,29,31,37,41},TEST_NUM=13;

long long PowMod(long long a,long long b,long long p)
{
	long long res=1LL;
	while(b)
	{
		if(b&1LL)
			res=1LL*res*a%p;
		a=1LL*a*a%p;
		b>>=1LL;
	}
	return res;
}

bool MillerRabin(long long a,long long n,long long d)
{
	long long x=PowMod(a,d,n);
	if(x==1||x==n-1)
		return true;
	while(d<n-1)
	{
		x=1LL*x*x%n;
		d=d*2LL;
		if(x==1)
			return false;
		if(x==n-1)
			return true;
	}
	return false;
}
bool isPrime(long long x)
{
	if(x<10)
	{
		if(x==2||x==3||x==5||x==7)
			return true;
		return false;
	}
	long long d=x-1;
	while((d&1LL)==0)
		d>>=1LL;
	for(int i=0;i<TEST_NUM;i++)
		if(TEST_VAL[i]<x&&!MillerRabin(TEST_VAL[i],x,d))
			return false;
	return true;
}

int main()
{
	int n,ans;
	long long x;
	while(scanf("%d",&n)!=EOF)
	{
		ans=0;
		while(n--)
		{
			scanf("%I64d",&x);
			ans+=isPrime(x);
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
