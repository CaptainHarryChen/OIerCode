#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=105,MAXK=55,INF=0x7F7F7F7F;

int N,K;
int w[MAXN],fa[MAXN],d[MAXN];
int las[MAXN],ls[MAXN],rs[MAXN];
int dep[MAXN],siz[MAXN];
int dp[MAXN][MAXN][MAXK];

void dfs(int u,int deep=0)
{
	siz[u]=1;
	dep[u]=deep;
	if(ls[u])
	{
		dfs(ls[u],deep+d[ls[u]]);
		siz[u]+=siz[ls[u]];
	}
	if(rs[u])
	{
		dfs(rs[u],dep[fa[u]]+d[rs[u]]);
		siz[u]+=siz[rs[u]];
	}
}

void DP(int u)
{
	if(ls[u])
		DP(ls[u]);
	if(rs[u])
		DP(rs[u]);
	if(ls[u]==0&&rs[u]==0)
	{
		for(int j=fa[u];j!=-1;j=fa[j])
			dp[u][j][0]=w[u]*(dep[u]-dep[j]),
			dp[u][j][1]=0;
		return;
	}
	for(int j=fa[u];j!=-1;j=fa[j])
		for(int k=0;k<=K;k++)
		{
			for(int l=0;l<=k;l++)
				if(dp[ls[u]][j][l]<INF&&dp[rs[u]][j][k-l]<INF)
					dp[u][j][k]=min(dp[u][j][k],dp[ls[u]][j][l]+dp[rs[u]][j][k-l]+w[u]*(dep[u]-dep[j]));
			for(int l=0;l<k;l++)
				if(dp[ls[u]][u][l]<INF&&dp[rs[u]][j][k-l-1]<INF)
					dp[u][j][k]=min(dp[u][j][k],dp[ls[u]][u][l]+dp[rs[u]][j][k-l-1]);
		}
}

int main()
{
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)
	{
		scanf("%d%d%d",w+i,fa+i,d+i);
		if(las[fa[i]]==0)
			ls[fa[i]]=i;
		else
			rs[las[fa[i]]]=i;
		las[fa[i]]=i;
	}
	fa[0]=-1;
	
	dfs(0);
	memset(dp,0x7F,sizeof dp);
	memset(dp[0],0,sizeof dp[0]); 
	DP(0);
	
	printf("%d\n",dp[ls[0]][0][K]);
	
	return 0;
}
