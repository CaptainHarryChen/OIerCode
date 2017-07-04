#include<cstdio>
#include<cstring>
#define MAXN 23
#define inside(x,y) (x>0&&y>0&&x<=n&&y<=m)
#define success(x,y) (x==gx&&y==gy)
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int n,m,sx,sy,gx,gy,ans;
int map[MAXN][MAXN];
void dfs(int x,int y,int step)
{
	if(step>=10||step>=ans)
		return;
	int tx,ty;
	for(int d=0;d<4;d++)
	{
		if(map[x+dir[d][0]][y+dir[d][1]])continue;
		tx=x;ty=y;
		while(inside(tx,ty)&&map[tx][ty]==0&&!success(tx,ty))
			tx+=dir[d][0],ty+=dir[d][1];
		if(!inside(tx,ty))continue;
		if(success(tx,ty))
		{
			ans=step+1;
			continue;
		}
		if(map[tx][ty])
		{
			map[tx][ty]=0;
			dfs(tx-dir[d][0],ty-dir[d][1],step+1);
			map[tx][ty]=1;
		}
	}
}
int main()
{
	while(1)
	{
		scanf("%d%d",&m,&n);
		if(n==0&&m==0)break;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				scanf("%d",&map[i][j]);
				if(map[i][j]==2)
				{sx=i;sy=j;map[i][j]=0;}
				if(map[i][j]==3)
				{gx=i;gy=j;map[i][j]=0;}
			}
		ans=0x7FFFFFFF;
		dfs(sx,sy,0);
		if(ans==0x7FFFFFFF)
			printf("-1\n");
		else
			printf("%d\n",ans);
	}
	return 0;
}
