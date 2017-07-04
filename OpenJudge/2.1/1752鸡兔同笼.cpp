#include<cstdio>
int main()
{
	int n,m;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d",&m);
		if(m%2==1){printf("0 0\n");continue;}
		printf("%d %d\n",(m+3)/4,m/2);
	}
	return 0;
}
