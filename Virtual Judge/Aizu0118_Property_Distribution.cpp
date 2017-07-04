#include<cstdio>
#include<cstring>
#define MAXN 105
#define inside(x,y) (x>0&&y>0&&x<=n&&y<=m)
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int n,m,cnt;
bool vis[MAXN][MAXN];
char map[MAXN][MAXN];
void dfs(int x,int y,char ch)
{
	vis[x][y]=1;
	int tx,ty;
	for(int d=0;d<4;d++)
	{
		tx=x+dir[d][0];
		ty=y+dir[d][1];
		if(inside(tx,ty)&&!vis[tx][ty]&&map[tx][ty]==ch)
			dfs(tx,ty,ch);
	}
}
int main()
{
	while(1)
	{
		scanf("%d%d",&n,&m);
		if(n==0&&m==0)
			break;
		for(int i=1;i<=n;i++)
			scanf("%s",map[i]+1);
		memset(vis,0,sizeof vis);
		cnt=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(!vis[i][j])
				{
					cnt++;
					dfs(i,j,map[i][j]);
				}
		printf("%d\n",cnt);
	}
	return 0;
}
