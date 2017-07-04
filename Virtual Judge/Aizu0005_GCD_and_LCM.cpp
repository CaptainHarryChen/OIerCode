#include<cstdio>
long long gcd(long long a,long long b)
{
	if(b==0LL)
		return a;
	return gcd(b,a%b);
}
int main()
{
	long long a,b;
	while(~scanf("%I64d%I64d",&a,&b))
	{
		long long d=gcd(a,b);
		printf("%I64d %I64d\n",d,a/d*b);
	}
	return 0;
}
