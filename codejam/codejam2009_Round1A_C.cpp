#include<cstdio>
const int MAXN=45;
int N,C;
double dp[MAXN];
double comb(int n,int m)
{
	if(n<m)
		return 0.0;
	double ret=1.0;
	for(int i=1;i<=m;i++)
		ret*=1.0*(n-i+1)/i;
	return ret;
}
double DP(int n)
{
	if(n==0)
		return 0.0;
	if(dp[n]>0.0)
		return dp[n];
	double ret=1.0,prob,unluck=0.0;
	for(int i=N>C-n?C-n:N;N-i<=n&&i>=0;i--)
	{
		prob=comb(C-n,i)*comb(n,N-i)/comb(C,N);
		if(i==N)
			unluck=prob;
		else
			ret+=prob*DP(n-N+i);
	}
	ret+=(unluck*ret)/(1.0-unluck);
	return dp[n]=ret;
}
int main()
{
	int T;
	scanf("%d",&T);
	for(int Case=1;Case<=T;Case++)
	{
		scanf("%d%d",&C,&N);
		for(int i=0;i<MAXN;i++)
			dp[i]=0.0;
		printf("Case #%d: %.10lf\n",Case,DP(C));
	}
	return 0;
}
