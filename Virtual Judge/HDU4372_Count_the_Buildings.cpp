#include<cstdio>
#define MAXN 2005
#define MOD 1000000007LL
long long C[MAXN][MAXN],S[MAXN][MAXN];
int main()
{
	int cas;
	scanf("%d",&cas);
	for(int i=0;i<MAXN;i++)
	{
		C[i][0]=C[i][i]=1;
		S[i][0]=0;S[i][i]=1;
		for(int j=1;j<i;j++)
		{
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
			S[i][j]=(S[i-1][j-1]+(i-1)*S[i-1][j]%MOD)%MOD;
		}
	}
	while(cas--)
	{
		int n,f,b;
		scanf("%d%d%d",&n,&f,&b);
		printf("%lld\n",C[f+b-2][f-1]*S[n-1][f+b-2]%MOD);
	}
	return 0;
}
