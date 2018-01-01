#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MR_a[]={2,3,5,7,11,13,17,19,23,29,31},MR=11;
const long long LLF=0x7FFFFFFFFFFFFFFFLL;

long long Rand(long long L,long long R)
{
	long long res=((1LL*rand())<<45LL)|((1LL*rand())<<30LL)|((1LL*rand())<<15LL)|(1LL*rand());
	return res%(R-L+1)+L;
}

long long mul_mod(long long a,long long b,long long p)
{
	long long res=0;
	a%=p;
	while(b)
	{
		if(b&1LL)
		{
			res+=a;
			if(res>=p)res-=p;
		}
		a+=a;
		if(a>=p)a-=p;
		b>>=1LL;
	}
	return res;
}
long long pow_mod(long long a,long long b,long long p)
{
	long long res=1;
	while(b)
	{
		if(b&1LL)
			res=mul_mod(res,a,p);
		a=mul_mod(a,a,p);
		b>>=1LL;
	}
	return res;
}

long long gcd(long long a,long long b)
{return b==0?a:gcd(b,a%b);}

bool Miller_Rabin(long long d,long long x,long long a)
{
	long long t=pow_mod(a,d,x);
	if(t==1||t==x-1)return true;
	while(d<x)
	{
		t=mul_mod(t,t,x);
		d<<=1LL;
		if(t==1)return false;
		if(t==x-1)return true;
	}
	return false;
}
bool is_prime(long long x)
{
	if(x==2||x==3||x==5)
		return true;
	if(x<=6)
		return false;
	long long d=x-1;
	while((d&1LL)==0)d>>=1LL;
	for(int i=0;i<MR&&MR_a[i]<x-1;i++)
		if(!Miller_Rabin(d,x,MR_a[i]))
			return false;
	return true;
}

long long Pollard_Rho(long long n)
{
	if(n==1)return 1;
	if((n&1)==0)return 2;
	long long x=Rand(1,n),y=x,c=Rand(1,n-1),d=1;
	while(d==1)
	{
		x=(mul_mod(x,x,n)+c)%n;
		y=(mul_mod(y,y,n)+c)%n;
		y=(mul_mod(y,y,n)+c)%n;
		if(x==y)return n;
		d=gcd(max(x-y,y-x),n);
	}
	return d;
}

long long solve(long long n)
{
	if(n==1)return LLF;
	if(is_prime(n))return n;
	long long d=Pollard_Rho(n);
	return min(solve(d),solve(n/d));
}

int main()
{
	int T;
	long long N;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld",&N);
		if(is_prime(N))
			puts("Prime");
		else
			printf("%lld\n",solve(N));
	}
	return 0;
}
