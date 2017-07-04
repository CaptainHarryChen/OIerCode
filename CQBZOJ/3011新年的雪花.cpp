#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
long long M,L;
int main()
{
	scanf("%lld%lld",&M,&L);
	long long edgcnt=3,edgsize=M;
	while(edgsize>L)
	{
		edgsize/=3;
		edgcnt*=4;
	}
	printf("%lld\n",edgsize*edgcnt);
	return 0;
}
