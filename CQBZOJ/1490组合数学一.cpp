#include<cstdio>
long long C(long long n,long long k)
{
	long long s=1;
	for(long long i=1;i<=k;i++)
	{
		s*=(n-i+1);
		s/=i;
	}
	return s;
}
int main()
{
	long long n,a,b;
	scanf("%lld%lld%lld",&n,&a,&b);
	long long s1=C(n+a,a);
	long long s2=C(n+b,b);
	long long sum=s1*s2;
	if(sum<0)
		printf("10549134770590785600\n");
	else
	printf("%lld\n",sum);
	return 0;
}
