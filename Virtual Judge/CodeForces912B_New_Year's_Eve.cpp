#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	long long n,k;
	scanf("%I64d%I64d",&n,&k);
	long long bit=1LL<<62LL;
	while((bit&n)==0)
		bit>>=1LL;
	if(k==1)
		printf("%I64d\n",n);
	else
		printf("%I64d\n",(bit<<1LL)-1LL);
	return 0;
}
