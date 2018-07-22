#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

long long f(long long b,long long n)
{return b>n?n:f(b,n/b)+n%b;}

int main()
{
	long long n,s,m;
	scanf("%lld%lld",&n,&s);
	if(n==s)
	{
		printf("%lld\n",n+1);
		return 0;
	}
	if(n<s)
	{
		puts("-1");
		return 0;
	}
	m=sqrt(n);
	for(long long b=2;b<=m;b++)
		if(f(b,n)==s)
		{
			printf("%lld\n",b);
			return 0;
		}
	for(long long p=m-1,b=(p>=1?(n-s)/p+1:0);p>=1;p--,b=(p>=1?(n-s)/p+1:0))
		if((n-s)%p==0&&n/b==p&&p<=s)
		{
			printf("%lld\n",b);
			return 0;
		}
	if(s==1)
	{
		printf("%lld\n",n);
		return 0;
	}
	puts("-1");
	
	return 0;
}
