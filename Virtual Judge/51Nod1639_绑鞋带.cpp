#include<cstdio>
const int MAXN=1005;

int n;
double p;

int main()
{
	scanf("%d",&n);
	p=1;
	for(int i=2;i<=n;i++)
		p=(p*2*(i-1))/(2*(i-1)+1);
	printf("%.6lf\n",p);
	
	return 0;
}
