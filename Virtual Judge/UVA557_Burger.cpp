#include<cstdio>
const int MAXN=100005;

double p[MAXN];

int main()
{
	p[2]=1;
	for(int i=4;i<MAXN;i+=2)
		p[i]=p[i-2]*0.5*0.5*(i-2)*(i-3)/(i/2.0-1)/(i/2.0-1);
	
	int T,n;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		printf("%.4lf\n",1-p[n]);
	}
	
	return 0;
}
