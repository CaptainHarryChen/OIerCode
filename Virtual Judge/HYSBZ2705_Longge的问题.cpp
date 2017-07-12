#include<cstdio>
#include<map>
using namespace std;
map<long long,long long> m;
long long fai(long long x)
{
	if(x==1)
		return 1;
	if(m.count(x)>0)
		return m[x];
	for(long long i=2;i*i<=x;i++)
		if(x%i==0)
		{
			long long p=1,q=x;
			while(q%i==0)
			{
				q/=i;
				p*=i;
			}
			return m[x]=(p-p/i)*fai(q);
		}
	return m[x]=x-1;
}
int main()
{
	long long n,ans=0;
	scanf("%lld",&n);
	for(long long i=1;i*i<=n;i++)
		if(n%i==0)
		{
			ans+=i*fai(n/i);
			if(i*i!=n)
				ans+=n/i*fai(i);
		}
	printf("%lld\n",ans);
	return 0;
}
