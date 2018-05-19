#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

int main()
{
	double n,m;
	scanf("%lf%lf",&n,&m);
	
	printf("%.6lf\n",1.0*n*(n-1)/2.0/m);
	
	return 0;
}
