#include<cstdio>
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i+=2)
		printf("%d ",i);
	for(int i=(n%2==0)?n:n-1;i>0;i-=2)
		printf("%d ",i);
	puts("");
	return 0;
}
