#include<cstdio>

long long gcd(long long a,long long b)
{return b==0?a:gcd(b,a%b);}
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

int main()
{
	long long x,y,m,n,L;
	scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&L);
	long long a=((m-n)%L+L)%L,b=L,c=((y-x)%L+L)%L;
	long long d=gcd(a,b);
	if(c%d!=0)
	{
		puts("Impossible");
		return 0;
	}
	long long p,q;
	a/=d;b/=d;c/=d;
	exgcd(a,b,p,q);
	p=(p*c)%L;
	p=(p%L+L)%L;
	printf("%lld\n",p);
	
	return 0;
}
