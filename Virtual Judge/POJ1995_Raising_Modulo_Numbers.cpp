#include<cstdio>
int mod_pow(int a,int b,int p)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=(int)(1LL*ret*a%p);
		a=(int)(1LL*a*a%p);
		b>>=1;
	}
	return ret;
}
int main()
{
	int T,n,p,ans,a,b;
	scanf("%d",&T);
	while(T--)
	{
		ans=0;
		scanf("%d%d",&p,&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&a,&b);
			ans=(ans+mod_pow(a,b,p))%p;
		}
		printf("%d\n",ans);
	}
	return 0;
}
