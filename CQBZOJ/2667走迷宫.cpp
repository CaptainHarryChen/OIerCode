#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#define MAXN 105
using namespace std;
const int dd[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
const char ddd[5]="DRUL";
int n,m,x1,y1,x2,y2,path[MAXN*MAXN],cnt,mincnt=999999,minpath[MAXN*MAXN];
bool maze[MAXN][MAXN],vis[MAXN][MAXN];
bool check(int x,int y)
{
	return x>0&&y>0&&x<=n&&y<=m;
}
void dfs(int x,int y)
{
	if(x==x2&&y==y2)
	{
		if(cnt<mincnt)
		{
			mincnt=cnt;
			memcpy(minpath,path,sizeof path);
		}
		return;
	}
	if(cnt==mincnt)return;
	for(int i=0;i<4;i++)
	{
		int tx=x+dd[i][0],ty=y+dd[i][1];
		if(check(tx,ty)&&maze[tx][ty]&&!vis[tx][ty])
		{
			path[++cnt]=i;
			vis[tx][ty]=1;
			dfs(tx,ty);
			vis[tx][ty]=0;
			path[cnt--]=0;
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&maze[i][j]);
	scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
	vis[x1][y1]=1;
	dfs(x1,y1);
	for(int i=1;i<=mincnt;i++)
		printf("%c",ddd[minpath[i]]);
	puts("");
	return 0;
}
