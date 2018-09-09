#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
	long long n;
	for(;;)
	{
		scanf("%lld",&n);
		if(n==0)
			break;
		bool flag=n<0;
		if(flag)
			n=-n;
		long long ans=-1;
		for(long long i=2;i*i<=n;i++)
			if(n%i==0)
			{
				long long cnt=0;
				while(n%i==0)
					n/=i,cnt++;
				if(ans==-1)
					ans=cnt;
				else
					ans=__gcd(ans,cnt);
			}
		if(n!=1)
			ans=1;
		while(flag&&ans%2==0)
			ans/=2;
		printf("%lld\n",ans);
	}
	
	return 0;
}
