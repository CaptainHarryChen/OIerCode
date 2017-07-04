#include<cstdio>
int grid[10][10],ans;
int vis[10][10],bone[40][2],cnt;
bool used[40];
void dfs(int x,int y)
{
	if(x>7)
	{
		ans++;
		for(int i=1;i<=7;i++)
		{
			for(int j=1;j<=8;j++)
				printf("%4d",vis[i][j]);
			printf("\n");
		}
		printf("\n\n");
		return;
	}
	if(y>8)
	{
		dfs(x+1,1);
		return;
	}
	if(vis[x][y])
	{
		dfs(x,y+1);
		return;
	}
	for(int i=1;i<=cnt;i++)
		if(!used[i])
		{
			if(grid[x][y]==bone[i][0])
			{
				if(y<8&&!vis[x][y+1]&&grid[x][y+1]==bone[i][1])
				{
					vis[x][y]=vis[x][y+1]=i;
					used[i]=1;
					dfs(x,y+2);
					used[i]=0;
					vis[x][y]=vis[x][y+1]=0;
				}
				if(x<7&&grid[x+1][y]==bone[i][1])
				{
					vis[x][y]=vis[x+1][y]=i;
					used[i]=1;
					dfs(x,y+1);
					used[i]=0;
					vis[x][y]=vis[x+1][y]=0;
				}
			}
			else if(grid[x][y]==bone[i][1])
			{
				if(y<8&&!vis[x][y+1]&&grid[x][y+1]==bone[i][0])
				{
					vis[x][y]=vis[x][y+1]=i;
					used[i]=1;
					dfs(x,y+2);
					used[i]=0;
					vis[x][y]=vis[x][y+1]=0;
				}
				if(x<7&&grid[x+1][y]==bone[i][0])
				{
					vis[x][y]=vis[x+1][y]=i;
					used[i]=1;
					dfs(x,y+1);
					used[i]=0;
					vis[x][y]=vis[x+1][y]=0;
				}
			}
		}
}
int main()
{
	for(int i=0;i<=6;i++)
		for(int j=i;j<=6;j++)
			bone[++cnt][0]=i,bone[cnt][1]=j;
	int T=0;
	while(~scanf("%d",&grid[1][1]))
	{
		if(T)puts("\n\n\n\n");
		printf("Layout #%d:\n\n\n",++T);
		for(int i=1;i<=7;i++)
			for(int j=1;j<=8;j++)
				if(i!=1||j!=1)scanf("%d",&grid[i][j]);
		for(int i=1;i<=7;i++)
		{
			for(int j=1;j<=8;j++)
				printf("%4d",grid[i][j]);
			printf("\n");
		}
		printf("\nMaps resulting from layout #%d are:\n\n\n",T);
		ans=0;
		dfs(1,1);
		printf("There are %d solution(s) for layout #%d.\n",ans,T);
	}
	return 0;
}
