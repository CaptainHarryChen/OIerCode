#include<cstdio>
int main()
{
	int n,ans=1;
	scanf("%d",&n);
	int a,b,i=2;
	scanf("%d%d",&a,&b);
	for(;b==a&&i<=n;i++)
		scanf("%d",&b);
	bool f=(a<b);
	a=b;
	for(;i<=n;)
		if(f)
		{
			for(i++;i<=n;i++)
			{
				scanf("%d",&b);
				if(b<a)break;
				a=b;
			}
			ans++;
			a=b;
			f=0;
		}
		else
		{
			for(i++;i<=n;i++)
			{
				scanf("%d",&b);
				if(b>a)break;
				a=b;
			}
			ans++;
			a=b;
			f=1;
		}
	printf("%d\n",ans);
	return 0;
}
