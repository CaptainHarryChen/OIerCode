#include<cstdio>
#include<algorithm>
using namespace std;
long long exgcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0)
	{
		x=1;y=0;
		return a;
	}
	long long x1,y1;
	long long d=exgcd(b,a%b,x1,y1);
	x=y1;
	y=x1-a/b*y1;
	return d;
}
int main()
{
	long long a,b,c,x,y,d,x1,x2,y1,y2;
	scanf("%lld%lld%lld",&a,&b,&c);
	scanf("%lld%lld%lld%lld",&x1,&x2,&y1,&y2);
	c=-c;
	if(a==0&&b==0)
	{
		if(c!=0)
			puts("0");
		else
			printf("%lld\n",1LL*(x2-x1+1)*(y2-y1+1));
	}
	else if(b==0)
	{
		if(c%a||c/a<x1||c/a>x2)
			puts("0");
		else
			printf("%lld\n",y2-y1+1);
	}
	else if(a==0)
	{
		if(c%b||c/b<y1||c/b>y2)
			puts("0");
		else
			printf("%lld\n",x2-x1+1);
	}
	else
	{
		d=exgcd(a,b,x,y);
		if(c%d)
			puts("0");
		else
		{
			a/=d;b/=d;c/=d;
			x*=c;
			y*=c;
			long long L,R;
			double temp,l1,r1,l2,r2;
			l1=1.0*(x1-x)/b;
			r1=1.0*(x2-x)/b;
			if(b<0)
				swap(l1,r1);
			l2=-1.0*(y1-y)/a;
			r2=-1.0*(y2-y)/a;
			if(a>0)
				swap(l2,r2);
			temp=max(l1,l2);
			if(temp-(long long)(temp)<1e-7)
				L=(long long)(temp);
			else
				L=(long long)(temp)+1;
			R=(long long)min(r1,r2);
			if(R<L)
				puts("0");
			else
				printf("%lld\n",R-L+1);
		}
	}
	return 0;
}
