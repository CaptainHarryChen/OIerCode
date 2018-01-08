#include<cstdio>
#include<cstring>
#include<set>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=1005;

int n,r;
int x[MAXN];
double y[MAXN];

int main()
{
	scanf("%d%d",&n,&r);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",x+i);
		y[i]=r;
		for(int j=1;j<i;j++)
			if(abs(x[i]-x[j])<=2*r)
				y[i]=max(y[i],y[j]+sqrt(4.0*r*r-1.0*abs(x[i]-x[j])*abs(x[i]-x[j])));
		printf("%.11lf",y[i]);
		if(i<n)putchar(' ');
	}
	puts("");
	return 0;
}
