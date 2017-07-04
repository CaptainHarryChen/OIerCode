#include<cstdio>
int main()
{
	int n,f[35]={0,1,2},p=3;
	while(~scanf("%d",&n))
	{
		if(!f[n])
			for(;p<=n;p++)
				f[p]=f[p-1]+f[p-2];
		printf("%d\n",f[n]);
	}
	return 0;
}
