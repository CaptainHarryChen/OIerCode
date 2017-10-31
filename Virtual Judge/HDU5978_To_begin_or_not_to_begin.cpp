#include<cstdio>
int main()
{
	int n;
	while(scanf("%d",&n)==1)
		printf("%d\n",(n&1)^1);
	return 0;
}
