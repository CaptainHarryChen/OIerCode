#include<cstdio>
#define inside(x,y) (x>0&&y>0&&x<=5&&y<=5)
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
bool vis[1000000];
int map[6][6],cnt;
void dfs(int x,int y,int step,int num)
{
	if(step>=6)
	{
		if(!vis[num])cnt++;
		vis[num]=1;
		return;
	}
	int tx,ty;
	for(int d=0;d<4;d++)
	{
		tx=x+dir[d][0];
		ty=y+dir[d][1];
		if(inside(tx,ty))
			dfs(tx,ty,step+1,num*10+map[tx][ty]);
	}
}
int main()
{
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++)
			scanf("%d",&map[i][j]);
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++)
			dfs(i,j,0,0);
	printf("%d\n",cnt);
	return 0;
}
