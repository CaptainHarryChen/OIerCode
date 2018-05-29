#include<cstdio>

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		if(n==0&&m==0)
			break;
		if(n%2==1&&m%2==1)
			puts("What a pity!");
		else
			puts("Wonderful!");
	}
	
	return 0;
}
