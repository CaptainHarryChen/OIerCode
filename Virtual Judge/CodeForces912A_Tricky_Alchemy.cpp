#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	long long A,B,x,y,z;
	scanf("%I64d%I64d%I64d%I64d%I64d",&A,&B,&x,&y,&z);
	printf("%I64d\n",max(x*2+y-A,0LL)+max(z*3+y-B,0LL));
	return 0;
}
