#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int dd[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int n,m,cnt,maxroom,size,vis[55][55],roomsize[2600];
bool wall[55][55][4];
bool check(int x,int y)
{
	return x>0&&y>0&&x<=n&&y<=m;
}
void dfs(int x,int y)
{
	vis[x][y]=cnt;
	size++;
	for(int i=0;i<4;i++)
	{
		int tx=x+dd[i][0],ty=y+dd[i][1];
		if(check(tx,ty)&&!vis[tx][ty]&&!wall[x][y][i])
			dfs(tx,ty);
	}
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++)
		for(int j=1,x;j<=m;j++)
		{
			scanf("%d",&x);
			wall[i][j][0]=x&1;
			wall[i][j][1]=x&2;
			wall[i][j][2]=x&4;
			wall[i][j][3]=x&8;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!vis[i][j])
			{
				cnt++;
				size=0;
				dfs(i,j);
				maxroom=max(maxroom,size);
				roomsize[cnt]=size;
			}
	int maxsize=maxroom,x=0,y=0;
	char c;
	for(int j=1;j<=m;j++)
	{
		for(int i=n;i>=2;i--)
			if(wall[i][j][1]&&vis[i-1][j]!=vis[i][j])
			{
				int s=roomsize[vis[i-1][j]]+roomsize[vis[i][j]];
				if(s>maxsize)
				{
					maxsize=s;
					x=i;y=j;c='N';
				}
			}
		if(j==m)break;
		for(int i=n;i>=1;i--)
			if(wall[i][j][2]&&vis[i][j+1]!=vis[i][j])
			{
				int s=roomsize[vis[i][j+1]]+roomsize[vis[i][j]];
				if(s>maxsize)
				{
					maxsize=s;
					x=i;y=j;c='E';
				}
			}
	}
	printf("%d\n%d\n",cnt,maxroom);
	printf("%d\n%d %d %c\n",maxsize,x,y,c);
	return 0;
}
