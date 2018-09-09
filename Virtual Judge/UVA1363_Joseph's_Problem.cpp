#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
	long long n,k;
	while(scanf("%lld%lld",&n,&k)!=EOF)
	{
		long long ans=0;
		for(long long i=1,nxt;i<=n&&i<=k;i=nxt+1)
		{
			nxt=min(n,k/(k/i));
			long long d=k/i;
			ans+=1LL*(k%i+k%i-(nxt-i)*d)*(nxt-i+1)/2LL;
			//printf("[%d,%d]:%I64d\n",i,nxt,1LL*(k%i+k%i-(nxt-i)*d)*(nxt-i+1)/2LL);
		}
		if(n>k)
			ans+=1LL*k*(n-k);
		printf("%lld\n",ans);
	}
	
	return 0;
}
