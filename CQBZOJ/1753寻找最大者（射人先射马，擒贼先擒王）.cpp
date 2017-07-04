#include<cstdio>
int main()
{
	int num,n,maxn=-2000000000,k;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&num);
		if(maxn<num)maxn=num,k=i-1;
	}
	printf("%d %d\n",maxn,k);
	return 0;
}
