#include<cstdio>
#define MAXN 105
int num[MAXN];
int main()
{
	int n,s,ans;
	while(1)
	{
		scanf("%d",&n);
		if(!n)break;
		s=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&num[i]);
			s^=num[i];
		}
		ans=0;
		for(int i=1;i<=n;i++)
			if(num[i]>(s^num[i]))
				ans++;
		printf("%d\n",ans);
	}
	return 0;
}
