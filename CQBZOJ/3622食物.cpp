#include<cstdio>
const int MAXN=505,MOD=10007,INV6=1668;

int main()
{
	int N=0,t;
	while(scanf("%1d",&t)!=EOF)
	{
		N=N*10+t;
		N%=MOD;
	}
	printf("%d\n",N*(N+1)%MOD*(N+2)%MOD*INV6%MOD);
	
	return 0;
}
