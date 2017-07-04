#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#define MAXN 25000000
using namespace std;
long long x,y,a,len,s[60][2];
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
bool check(long long y,long long m)
{
	long long s=ksm(x,y,m);
	if(s==1)return 1;
	return 0;
}
int main()
{
	while(~scanf("%I64d%I64d%I64d",&x,&y,&a))
	{
		long long p=y/(x-1);
		long long a0=a/(gcd(a,p));
		if(gcd(a0,x)!=1){printf("Impossible!\n");continue;}
		long long ans=phi(a0),aa=ans;
		memset(s,0,sizeof s);
		len=0;
		for(long long j=2;j*j<=ans;j++)
			if(ans%j==0)
			{
				s[len][0]=j;
				while(ans%j==0){ans/=j;s[len][1]++;}
				len++;
			}
		if(ans>1){s[len][0]=ans;s[len++][1]=1;}
		for(long long j=0;j<len;j++)
			for(long long k=1;k<=s[j][1];k++)
				if(check(aa/s[j][0],a0))
					aa/=s[j][0];
		printf("%I64d\n",aa);
	}
	return 0;
}