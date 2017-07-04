#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
long long X;
long long gcd(long long a,long long b)
{
	if(b==0)return a;
	return gcd(b,a%b);
}
long long phi(long long x)
{
	long long m=sqrt(x+0.5);
	long long ans=x;
	for(long long i=2;i<=m;i++)
		if(x%i==0)
		{
			ans=ans/i*(i-1);
			while(x%i==0)x/=i;
		}
	if(x>1)ans=ans/x*(x-1);
	return ans;
}
long long mul(long long a,long long b,long long p)
{
	long long m=0,i;
	for(i=1;i<=b;i<<=1,a=(a<<1)%p)
		if(i&b)
			m=(m+a)%p;
	return m;
}
long long ksm(long long a,long long b,long long p)
{
	long long m=1;
	for(;b;a=mul(a,a,p),b>>=1)
		if(b&1)
			m=mul(m,a,p);
	return m;
}
int main()
{
	long long a,b,c,ans;
	while(~scanf("%I64d",&X)&&X)
	{
		a=(ksm(2,2*X+1,29)-1)%29;
		b=mul((ksm(3,X+1,29)-1),15,29);
		c=mul((ksm(22,X+1,29)-1),18,29);
		ans=mul(a,b,29);
		ans=mul(ans,c,29);
		printf("%I64d\n",ans);
	}
	return 0;
}