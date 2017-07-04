#include<cstdio>
#include<algorithm>
#include<cmath>
using std::abs;
using std::min;
int main()
{
	int a,b;
	while(~scanf("%d%d",&a,&b))
		printf("%d\n",min(a,b)!=(int)(abs(a-b)*(1.0+sqrt(5.0))/2.0));
	return 0;
}
