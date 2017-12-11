#include<cstdio>
const int MAXN=10005,MOD=2007;

int N,F[MAXN],G[MAXN];

int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d",&F[i]);
	G[1]=1/F[1];
	for(int i=1;i<=N;i++)
		for(int j=i*2;j<=N;j+=i)
			G[j]=((G[j]-1/F[1]*F[j/i]*G[i])%MOD+MOD)%MOD;
	for(int i=1;i<N;i++)
		printf("%d ",G[i]);
	printf("%d\n",G[N]);
	return 0;
}
