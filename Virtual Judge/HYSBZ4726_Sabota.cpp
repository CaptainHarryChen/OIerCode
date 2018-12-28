#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=500005;
const double EPS=1e-8;

int dcmp(double a,double b)
{
	if(abs(a-b)<=EPS)
		return 0;
	return a<b?-1:1;
}

int n,k,P[MAXN],siz[MAXN];
vector<int> son[MAXN];
double dp[MAXN],ans=0;

void DP(int u)
{
	if(siz[u]==1)
	{
		dp[u]=1;
		return;
	}
	for(int i=0;i<(int)son[u].size();i++)
	{
		int v=son[u][i];
		DP(v);
		dp[u]=max(dp[u],min(dp[v],1.0*siz[v]/(siz[u]-1)));
	}
	if(siz[u]>k)
		ans=max(ans,dp[u]);
}

int main()
{
	scanf("%d%d",&n,&k);
	if(n==1)
	{
		printf("%d\n",n-k);
		return 0;
	}
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&P[i]);
		son[P[i]].push_back(i);
	}
	for(int i=n;i>=1;i--)
		siz[i]++,siz[P[i]]+=siz[i];
	
	DP(1);
	printf("%.10f\n",ans);
	
	return 0;
}
