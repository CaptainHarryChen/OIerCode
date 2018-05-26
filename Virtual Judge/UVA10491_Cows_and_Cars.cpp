#include<cstdio>

double a,b,c;
	
int main()
{
	while(scanf("%lf%lf%lf",&a,&b,&c)!=EOF)
		printf("%.5lf\n",a/(a+b)*b/(a+b-c-1)+b/(a+b)*(b-1)/(a+b-c-1));
	return 0;
}
