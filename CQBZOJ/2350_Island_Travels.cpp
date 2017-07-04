#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
#define MAXR 53
#define MAXN 17
#define MAXS 65600
#define check(a,b) (a>0&&b>0&&a<=R&&b<=C)
#define code(a,b) ((a-1)*C+b)
#define get_x(t) ((t-1)/C+1)
#define get_y(t) ((t-1)%C+1)
const int dd[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int R,C;
char map[MAXR][MAXR];
int island[MAXR][MAXR],n,step[MAXR][MAXR],E[MAXN][MAXN];
bool vis[MAXN],vis2[MAXN],used[MAXR][MAXR];
int dp[MAXS][MAXN];
queue<int>Q;
void mark_island(int x,int y,int flag)
{
	island[x][y]=flag;
	for(int i=0;i<4;i++)
	{
		int tx=x+dd[i][0],ty=y+dd[i][1];
		if(check(tx,ty)&&map[tx][ty]=='X'&&!island[tx][ty])
			mark_island(tx,ty,flag);
	}
}
void find_path(int x,int y)
{
	used[x][y]=1;
	for(int i=0;i<4;i++)
	{
		int tx=x+dd[i][0],ty=y+dd[i][1];
		if(check(tx,ty)&&map[tx][ty]=='S'&&!used[tx][ty])
		{
			Q.push(code(tx,ty));
			step[tx][ty]=1;
			used[tx][ty]=1;
		}
		if(check(tx,ty)&&map[tx][ty]=='X'&&!used[tx][ty])
			find_path(tx,ty);
	}
}
int main()
{
	freopen("island.in","r",stdin);
	freopen("island.out","w",stdout);
	scanf("%d%d",&R,&C);
	for(int i=1;i<=R;i++)
		scanf("%s",map[i]+1);
	for(int i=1;i<=R;i++)
		for(int j=1;j<=C;j++)
			if(map[i][j]=='X'&&!island[i][j])
				mark_island(i,j,++n);
	memset(E,0x3F,sizeof E);
	for(int i=1;i<=n;i++)E[i][i]=0;
	for(int i=1;i<=R;i++)
		for(int j=1;j<=C;j++)
			if(map[i][j]=='X'&&!vis2[island[i][j]])
			{
				while(!Q.empty())Q.pop();
				memset(used,0,sizeof used);
				memset(vis,0,sizeof vis);
				find_path(i,j);
				int flag=island[i][j];
				vis[flag]=vis2[flag]=1;
				while(!Q.empty())
				{
					int t=Q.front();Q.pop();
					int x=get_x(t),y=get_y(t);
					for(int d=0;d<4;d++)
					{
						int tx=x+dd[d][0],ty=y+dd[d][1];
						if(map[tx][ty]=='X'&&!vis[island[tx][ty]])
						{
							E[flag][island[tx][ty]]=step[x][y];
							vis[island[tx][ty]]=1;
						}
						if(map[tx][ty]=='S'&&!used[tx][ty])
						{
							Q.push(code(tx,ty));
							used[tx][ty]=1;
							step[tx][ty]=step[x][y]+1;
						}
					}
				}
			}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
		{
			if(i==k)continue;
			for(int j=1;j<=n;j++)
			{
				if(j==i||j==k)continue;
				E[i][j]=min(E[i][j],E[i][k]+E[k][j]);
			}
		}
	memset(dp,0x3F,sizeof dp);
	for(int i=1;i<=n;i++)
		dp[1<<(i-1)][i]=0;
	for(int s=1;s<(1<<n);s++)
		for(int i=1;i<=n;i++)
			if((1<<(i-1))&s)
			{
				for(int j=1;j<=n;j++)
					if(i!=j&&((1<<(j-1))&s))
					{
						int ss=s-(1<<(i-1));
						dp[s][i]=min(dp[s][i],dp[ss][j]+E[j][i]);
					}
			}
	int ans=0x7FFFFFFF;
	for(int i=1;i<=n;i++)
		ans=min(ans,dp[(1<<n)-1][i]);
	printf("%d\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
