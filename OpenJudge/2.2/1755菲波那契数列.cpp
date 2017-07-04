#include<cstdio>
int main()
{
	int n,num[25]={1,1},a,p=2;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d",&a);
		if(!num[a-1])
			for(;p<a;p++)
				num[p]=num[p-1]+num[p-2];
		printf("%d\n",num[a-1]);
	}
	return 0;
}
