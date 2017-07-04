#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#define MAXN 210
#define MAXM 85
using namespace std;
const int dd[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
int n,m,xx[2],yy[2],cnt,maxcnt,step[MAXN][MAXM];
bool maze[MAXN][MAXM],vis[MAXN][MAXM];
char s[MAXM];
bool check(int x,int y)
{
	return x>0&&y>0&&x<=n&&y<=m;
}
void dfs(int x,int y)
{
	for(int i=0;i<4;i++)
	{
		int tx=x+dd[i][0],ty=y+dd[i][1];
		if(check(tx,ty)&&maze[tx][ty]&&!vis[tx][ty])
		{
			cnt++;
			if(cnt>=step[tx][ty])
			{cnt--;continue;}
			step[tx][ty]=cnt;
			vis[tx][ty]=1;
			dfs(tx,ty);
			vis[tx][ty]=0;
			cnt--;
		}
	}
}
bool check_side(int x,int y)
{
	return x==1||y==1||x==n||y==m;
}
int main()
{
	scanf("%d%d",&m,&n);
	gets(s);
	n=n*2+1;
	m=m*2+1;
	for(int i=1,kk=0;i<=n;i++)
	{
		gets(s);
		for(int j=0;j<m;j++)
		{
			if(s[j]==' ')
			{
				maze[i][j+1]=1;
				if(check_side(i,j+1))
				{xx[kk]=i;yy[kk++]=j+1;}
			}
			else if(s[i]!='\n')
				maze[i][j+1]=0;
		}
	}
	memset(step,127,sizeof step);
	vis[xx[0]][yy[0]]=vis[xx[1]][yy[1]]=1;
	dfs(xx[0],yy[0]);
	memset(vis,0,sizeof vis);
	cnt=0;
	vis[xx[0]][yy[0]]=vis[xx[1]][yy[1]]=1;
	dfs(xx[1],yy[1]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(step[i][j]!=2139062143)
				maxcnt=max(maxcnt,step[i][j]);
	printf("%d\n",(maxcnt+1)/2);
	return 0;
}
