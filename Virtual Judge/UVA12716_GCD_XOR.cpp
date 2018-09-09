#include<cstdio>
const int MAXN=30000005;

long long ans[MAXN];

int main()
{
	for(int g=1;g<MAXN;g++)
		for(int i=g+g;i<MAXN;i+=g)
			if((i^(i-g))==g)
				ans[i]++;
	for(int i=1;i<MAXN;i++)
		ans[i]+=ans[i-1];
	int T;
	scanf("%d",&T);
	for(int test=1;test<=T;test++)
	{
		int n;
		scanf("%d",&n);
		printf("Case %d: %lld\n",test,ans[n]);
	}
	
	return 0;
}
