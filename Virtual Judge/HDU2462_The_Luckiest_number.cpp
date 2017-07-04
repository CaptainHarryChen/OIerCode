#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
long long L,len,s[60][2];
long long Gcd(long long a,long long b)
{
	if(b==0)
		return a;
	return Gcd(b,a%b);
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
bool check(long long x,long long m)
{
	long long s=ksm(10,x,m);
	if(s==1)return 1;
	return 0;
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
int main()
{
	//freopen("test.txt","r",stdin);
	long long i=0;
	while(~scanf("%I64d",&L)&&L!=0)
	{
		long long m=9*L;
		m=m/Gcd(L,8);
		if(Gcd(m,10)!=1){printf("Case %I64d: 0\n",++i);continue;}
		long long ans=phi(m),aa=ans;
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
				if(check(aa/s[j][0],m))
					aa/=s[j][0];
		printf("Case %I64d: %I64d\n",++i,aa);
	}
	return 0;
}