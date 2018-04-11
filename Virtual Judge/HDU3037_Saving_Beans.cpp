#include<cstdio>

void exgcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0)
		x=1,y=0;
	else
	{
		long long x1,y1;
		exgcd(b,a%b,x1,y1);
		x=y1;
		y=x1-(a/b)*y1;
	}
}
long long inv(long long x,long long p)
{
	long long i,t;
	exgcd(x,p,i,t);
	i=(i%p+p)%p;
	return i;
}


long long C(long long n,long long r,long long MOD)
{
	if(n<r)
		return 0;
	if(r==0)
		return 1;
	long long ans=1LL;
	ans=C(n/MOD,r/MOD,MOD);
	n%=MOD,r%=MOD;
	long long a=1,b=1;
	for(int i=n;i>n-r;i--)
		a=(a*i)%MOD;
	for(int i=1;i<=r;i++)
		b=(b*i)%MOD;
	ans=(ans*a%MOD*inv(b,MOD))%MOD;
	return ans;
}

int main()
{
	long long T,n,m,p;
	scanf("%I64d",&T);
	while(T--)
	{
		scanf("%I64d%I64d%I64d",&n,&m,&p);
		printf("%I64d\n",C(n+m,m,p));
	}
	return 0;
}
