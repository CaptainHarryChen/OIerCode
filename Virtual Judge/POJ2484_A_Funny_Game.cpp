#include<cstdio>
int main()
{
	int n;
	for(;;)
	{
		scanf("%d",&n);
		if(n==0)
			break;
		if(n<3)
			puts("Alice");
		else
			puts("Bob");
	}
	return 0;
}
