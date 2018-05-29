#include<cstdio>

int main()
{
	int n,m,a,b;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&a,&b);
			ans^=(a>b?a-b-1:b-a-1);
		}
		if(ans)
			puts("I WIN!");
		else
			puts("BAD LUCK!");
	}
	return 0;
}
