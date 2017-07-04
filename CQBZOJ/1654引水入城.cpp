#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define MAXN 505
#define check(a,b) (a>0&&b>0&&a<=n&&b<=m)
const int dd[4][2]={{1,0},{0,-1},{-1,0},{0,1}};
int n,m,h[MAXN][MAXN],st[MAXN],ed[MAXN],dp[MAXN];
bool vis[MAXN][MAXN];
void dfs(int x,int y)
{
	vis[x][y]=1;
	for(int i=0;i<4;i++)
	{
		int tx=x+dd[i][0],ty=y+dd[i][1];
		if(check(tx,ty)&&h[tx][ty]<h[x][y]&&!vis[tx][ty])
			dfs(tx,ty);
	}
}
void dfs2(int x,int y,int k)
{
	if(x==n)
	{st[k]=min(st[k],y);ed[k]=max(ed[k],y);}
	for(int i=0;i<4;i++)
	{
		int tx=x+dd[i][0],ty=y+dd[i][1];
		if(check(tx,ty)&&h[tx][ty]<h[x][y])
			dfs2(tx,ty,k);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&h[i][j]);
	for(int j=1;j<=m;j++)
		dfs(1,j);
	int cnt=0;
	for(int j=1;j<=m;j++)
		if(!vis[n][j])
			cnt++;
	if(cnt>0)
		printf("0\n%d\n",cnt);
	else
	{
		printf("1\n");
		for(int j=1;j<=m;j++)
		{
			st[j]=m+1;
			ed[j]=0;
			dfs2(1,j,j);
		}
		memset(dp,0x7F,sizeof dp);
		dp[0]=0;
		for(int j=st[1];j<=ed[1];j++)
			dp[j]=1;
		for(int i=2;i<=m;i++)
			for(int j=m;j>0;j--)
				if(st[i]<=j&&ed[i]>=j)
					dp[j]=min(dp[st[i]-1]+1,dp[j]);
		printf("%d\n",dp[m]);
	}
	return 0;
}
