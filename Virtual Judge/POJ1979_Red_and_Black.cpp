#include<cstdio>
#include<cstring>
#define MAXN 23
#define inside(x,y) (x>0&&y>0&&x<=n&&y<=m)
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int n,m,cnt;
char map[MAXN][MAXN];
bool vis[MAXN][MAXN];
void dfs(int x,int y)
{
	cnt++;
	vis[x][y]=1;
	int tx,ty;
	for(int d=0;d<4;d++)
	{
		tx=x+dir[d][0];
		ty=y+dir[d][1];
		if(inside(tx,ty)&&map[tx][ty]!='#'&&!vis[tx][ty])
			dfs(tx,ty);
	}
}
int main()
{
	while(1)
	{
		scanf("%d%d",&m,&n);
		if(n==0&&m==0)
			break;
		int stx,sty;
		for(int i=1;i<=n;i++)
			scanf("%s",map[i]+1);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(map[i][j]=='@')
				{
					stx=i;
					sty=j;
				}
		memset(vis,0,sizeof vis);
		cnt=0;
		dfs(stx,sty);
		printf("%d\n",cnt);
	}
	return 0;
}
