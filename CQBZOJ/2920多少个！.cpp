#include<cstdio>
int main()
{
	int a,b=0;
	scanf("%d",&a);
	b+=(a/4)*2;
	if(a%4!=0)
	b++;
	printf("%d\n",b);
	return 0;
}
