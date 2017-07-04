#include<cstdio>
#define MAXN 1005
int a[MAXN];
int main()
{
	int n,k,sg,i;
	while(~scanf("%d%d",&n,&k))
	{
		for(i=1;i<=n;i++)
			scanf("%d",&a[i]);
		if(k==1)
		{
			puts("Alice");
			continue;
		}
		sg=0;
		for(i=n;i>1;i-=2)
			sg^=(a[i]-a[i-1]-1);
		if(i==1)
		{
			if(k==2)
				sg^=a[1]-1;
			else
				sg^=a[1];
		}
		if(sg)
			puts("Alice");
		else
			puts("Bob");
	}
	return 0;
}