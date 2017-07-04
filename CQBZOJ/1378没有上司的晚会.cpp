#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=6005;
int n,val[MAXN];
int fa[MAXN];
vector<int>son[MAXN];
int dp[MAXN][2];
int DP(int x,int f)
{
	if(dp[x][f]!=-0x7FFFFFFF)
		return dp[x][f];
	int ret=0;
	for(int i=0,temp;i<(int)son[x].size();i++)
	{
		temp=0;
		temp=max(temp,DP(son[x][i],0));
		if(!f)temp=max(temp,DP(son[x][i],1));
		ret+=temp;
	}
	if(f)ret+=val[x];
	return dp[x][f]=ret;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&val[i]);
		dp[i][0]=dp[i][1]=-0x7FFFFFFF;
	}
	for(int i=1,a,b;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		fa[a]=b;
		son[b].push_back(a);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		if(fa[i]==0)
			ans+=max(DP(i,0),DP(i,1));
	printf("%d\n",ans);
	return 0;
}
