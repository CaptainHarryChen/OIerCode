#include<cstdio>
#include<cmath>
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	if(sqrt(n)>k)
	{printf("-1\n");return 0;}
	int i;
	for(i=n-k+1;i>0;i-=k)
		for(int j=i;j<=i+k-1;j++)
			printf("%d ",j);
	for(int j=1;j<=i+k-1;j++)
		printf("%d ",j);
	printf("\n");
	return 0;
}
