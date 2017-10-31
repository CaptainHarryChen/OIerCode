#include<cstdio>
const int MAXN=1005;
long long m[MAXN],r[MAXN];
long long gcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0LL)
	{
		x=1LL;y=0LL;
		return a;
	}
	long long xx,yy,d=gcd(b,a%b,xx,yy);
	x=yy;
	y=xx-a/b*yy;
	return d;
}
long long gcd(long long a,long long b)
{return b==0LL?a:gcd(b,a%b);}
long long lcm(long long a,long long b)
{return a/gcd(a,b)*b;}
bool solve(long long a,long long b,long long c,long long &x,long long &y)
{
	long long d;
	d=gcd(a,b,x,y);
	if(c%d)return false;
	a/=d;b/=d;c/=d;
	x*=c;y*=c;
	x=(x%b+b)%b;
	return true;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",m+i,r+i);
	long long x=0,k1,k2,l;
	bool flag=true;
	for(int i=1;i<n;i++)
	{
		if(!solve(m[i],m[i+1],r[i+1]-r[i],k1,k2))
		{flag=false;break;}
		x=m[i]*k1+r[i];
		l=lcm(m[i],m[i+1]);
		x=(x%l+l)%l;
		m[i+1]=l;
		r[i+1]=x;
	}
	if(flag)
		printf("%lld\n",r[n]);
	else
		puts("-1");
	return 0;
}
