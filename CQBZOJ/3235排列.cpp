#include<cstdio>
#define MOD 1000000007L
#define MAXN 1000
int ans[MAXN+5][MAXN+5];
void make_ans()
{
	for(int n=1;n<=MAXN;n++)
	{
		ans[n][0]=1;
		ans[n][n-1]=1;
		for(int k=1;k<n-1;k++)
			ans[n][k]=(int)(((long long)ans[n-1][k]*(long long)(k+1)+(long long)ans[n-1][k-1]*(long long)(n-k))%MOD);
	}
}
int main()
{
	make_ans();
	int t,n,k;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&k);
		printf("%d\n",ans[n][k]);
	}
	return 0;
}
