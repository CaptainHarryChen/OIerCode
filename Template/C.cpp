#include<cstdio>
#define MOD 1000000007LL
long long ksm(long long a,long long b,long long p)
{
	long long ret=1;
	for(;b>0;b>>=1,a=(a*a)%p)
		if(b&1)
			ret=(ret*a)%p;
	return ret;
}
long long C(long long a,long long b)
{
    long long s1=1,s2=1;
	for(long long i=a-b+1;i<=a;i++)
		s1=(s1*i)%MOD;
	for(long long i=1;i<=b;i++)
		s2=(s2*i)%MOD;
	return (s1*ksm(s2,MOD-2,MOD))%MOD;
}
int main()
{
    freopen("C_data.in","r",stdin);
    long long a,b;
    scanf("%I64d%I64d",&a,&b);
    printf("%I64d\n",C(a,b));
    return 0;
}
