#include<cstdio>
#include<iostream>
using namespace std;
int arr[505][505],f[505][505],dd[4][2]={{0,1},{1,0},{-1,0},{0,-1}},r,c;
bool hefa(int x,int y)
{
	if(y>0&&x>0&&x<=r&&y<=c)
		return 1;
	return 0;
}
int dfs(int x,int y)
{
	if(f[x][y])
		return f[x][y];
	f[x][y]=1;
	for(int i=0;i<4;i++)
	{
		int tx=x+dd[i][0],ty=y+dd[i][1];
		if(hefa(tx,ty)&&arr[tx][ty]>arr[x][y])
		{
			int s=dfs(tx,ty)+1;
			f[x][y]=f[x][y]>s?f[x][y]:s;
		}
	}
	return f[x][y];
}
int main()
{
	cin>>r>>c;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			scanf("%d",&arr[i][j]);
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			if(!f[i][j])
				f[i][j]=dfs(i,j);
	int maxf=0;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			if(maxf<f[i][j])
				maxf=f[i][j];
	printf("%d\n",maxf);
	return 0;
}
