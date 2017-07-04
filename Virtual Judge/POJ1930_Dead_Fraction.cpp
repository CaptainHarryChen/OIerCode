#include<cstdio>
#include<cstring>
long long gcd(long long a,long long b)
{return b==0LL?a:gcd(b,a%b);}
int main()
{
	long long n;
	char in[20];
	while(1)
	{
		scanf("%s",in);
		if(strlen(in)==1)
			break;
		sscanf(in+2,"%lld",&n);
		long long i=strlen(in)-3LL,st=i,ed=2LL,b=0LL,a,temp=9LL,g,tn=n;
		for(long long j=1;j<=st-ed;j++)
			temp*=10LL;
		tn/=10LL;
		long long mn=0x7FFFFFFFFFFFFFFFLL,ans;
		while(i>=ed)
		{
			b+=(temp/=10LL);
			a=n-tn;
			g=gcd(a,b);
			if(mn>b/g)
			{
				mn=b/g;
				ans=a/g;
			}
			i--;
			tn/=10LL;
		}
		printf("%lld/%lld\n",ans,mn);
	}
	return 0;
}
