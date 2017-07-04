#include<cstdio>
int main()
{
	int num,cnt=0;
	for(int i=1;i<=10;i++)
	{
		scanf("%d",&num);
		cnt+=(num>=90);
	}
	printf("%d\n",cnt);
	return 0;
}
