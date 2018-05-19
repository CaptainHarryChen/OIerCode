#include<cstdio>
#include<cstring>
const long long MAXN=17,MAXM=100000005,MAXP=30;

long long cnt;
long long fac[MAXP],ind[MAXP];

long long pow(long long a,long long b)
{
	long long ret=1;
	while(b)
	{
		if(b&1)
			ret=ret*a;
		a=a*a;
		b>>=1;
	}
	return ret;
}

int main()
{
	long long n,m;
	scanf("%lld%lld",&n,&m);
	
	cnt=0;
	memset(fac,0,sizeof fac);
	memset(ind,0,sizeof ind);
	long long X=m;
	for(long long p=2;p*p<=X;p++)
		if(X%p==0)
		{
			fac[++cnt]=p;
			while(X%p==0)
				X/=p,ind[cnt]++;
		}
	if(X!=1)
		fac[++cnt]=X,ind[cnt]++;
	
	long long ans=0,temp,flag;
	for(long long s=0;s<(1<<cnt);s++)
	{
		if(__builtin_popcount(s)&1)
			flag=-1;
		else
			flag=1;
		temp=1;
		for(long long i=0,bit=1;i<cnt;i++,bit<<=1)
			if(s&bit)
				temp*=fac[i+1];
		temp=m/temp;
		ans+=flag*pow(temp,n);
	}
	printf("%lld\n",ans);
	
	return 0;
}
