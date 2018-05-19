#include<cstdio>
const int MAXN=25;
long long fac[MAXN];
int main()
{
	fac[0]=1;
	for(int i=1;i<MAXN;i++)
		fac[i]=fac[i-1]*i;
	int n;
	while(~scanf("%d",&n))
	{
		long long ans=0;
		ans+=fac[n];
		for(int i=1,flag=-1;i<=n;i++,flag=-flag)
			ans+=flag*fac[n]/fac[i];
		printf("%lld\n",ans);
	}
	
	return 0;
}
