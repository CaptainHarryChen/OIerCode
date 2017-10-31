#include<cstdio>
long long exgcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0LL)
	{
		x=1LL;
		y=0LL;
		return a;
	}
	long long xx,yy,d;
	d=exgcd(b,a%b,xx,yy);
	x=yy;
	y=xx-a/b*yy;
	return d;
}
int main()
{
	long long X,Y,M,N,L;
	while(scanf("%lld%lld%lld%lld%lld",&X,&Y,&M,&N,&L)==5)
	{
		long long a,b,c,d,x,y;
		a=((M-N)%L+L)%L;
		b=L;
		c=((Y-X)%L+L)%L;
		d=exgcd(a,b,x,y);
		if(c%d)
		{
			puts("Impossible");
			continue;
		}
		a/=d;b/=d;c/=d;
		x=(x*c)%b;
		x=(x+b)%b;
		printf("%lld\n",x);
	}
	return 0;
}
