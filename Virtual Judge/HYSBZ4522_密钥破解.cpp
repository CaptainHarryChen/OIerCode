#include<cstdio>
#include<cstdlib>

long long MulMod(long long a,long long b,long long p)
{
	long long res=0;
	while(b)
	{
		if(b&1LLU)
			res=(res+a>=p?res+a-p:res+a);
		b>>=1LLU;
		a=(a+a>=p?a+a-p:a+a);
	}
	return res;
}
long long PowMod(long long a,long long b,long long p)
{
	long long res=1;
	while(b)
	{
		if(b&1LLU)
			res=MulMod(res,a,p);
		b>>=1LLU;
		a=MulMod(a,a,p);
	}
	return res;
}
void exgcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0)
	{
		x=1;y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=x*(a/b);
}
long long gcd(long long a,long long b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}
long long Inv(long long a,long long p)
{
	long long x,y;
	exgcd(a,p,x,y);
	x=(x+p)%p;
	return x;
}

long long PollardRho(long long n)
{
	static long long t=0;
	t++;
	long long a=rand(),b=a,g;
	for(;;)
	{
		a=(MulMod(a,a,n)+t)%n;
		b=(MulMod(b,b,n)+t)%n;
		b=(MulMod(b,b,n)+t)%n;
		if(a==b)
			return 1;
		g=gcd(a>b?a-b:b-a,n);
		if(g>1)
			return g;
	}
	return 1;
}
int main()
{
	long long e,d,N,c,n;
	scanf("%lld%lld%lld",&e,&N,&c);
	long long p,q,r;
	do
	{
		p=PollardRho(N);
	}while(p==1);
	q=N/p;
	r=(p-1)*(q-1);
	d=Inv(e,r);
	n=PowMod(c,d,N);
	
	printf("%lld %lld\n",d,n);
	
	return 0;
}
