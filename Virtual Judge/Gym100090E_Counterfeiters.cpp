#include<cstdio>
int main()
{
	int a,b;
	scanf("%d%d",&a,&b);
	printf("%.7lf\n",1.0*a/(a+b)*a/100.0+1.0*b/(a+b)*b/100.0);
	return 0;
}
