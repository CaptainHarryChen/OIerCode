#include<cstdio>

int main()
{
	long long ans=0,bit;
	int T,n;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		ans=1LL*(n+1)*n/2LL;
		bit=1;
		while(bit<=n)
		{
			ans-=bit*2LL;
			bit<<=1LL;
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
