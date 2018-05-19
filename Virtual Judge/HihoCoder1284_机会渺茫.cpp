#include<cstdio>
#include<set>
using namespace std;

long long gcd(long long a,long long b)
{return b==0?a:gcd(b,a%b);}

set<long long>fac;

int main()
{
	long long N,M;
	scanf("%lld%lld",&N,&M);
	long long a=0,b=0,c=0;
	for(long long i=1;i*i<=N;i++)
		if(N%i==0)
		{
			fac.insert(i);
			a++;
			if(N/i!=i)
				fac.insert(N/i),a++;
		}
	for(long long i=1;i*i<=M;i++)
		if(M%i==0)
		{
			c+=fac.count(i);
			b++;
			if(M/i!=i)
				c+=fac.count(M/i),b++;
		}
	long long d=gcd(a*b,c);
	printf("%lld %lld\n",a*b/d,c/d);
	
	return 0;
}
