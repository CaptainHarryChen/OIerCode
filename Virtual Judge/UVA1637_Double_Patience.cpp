#include<cstdio>
#include<cstring>

double dp[5][5][5][5][5][5][5][5][5];
bool vis[5][5][5][5][5][5][5][5][5];
char str[9][4][3];

double dfs(int a,int b,int c,int d,int e,int f,int g,int h,int i)
{
	if(vis[a][b][c][d][e][f][g][h][i])
		return dp[a][b][c][d][e][f][g][h][i];
	double tmp=0;
	int cnt=0;
	int st[]={a,b,c,d,e,f,g,h,i};
	for(int x=0;x<9;x++)
		for(int y=x+1;y<9;y++)
			if(st[x]>0&&st[y]>0&&str[x][st[x]-1][0]==str[y][st[y]-1][0])
			{
				cnt++;
				st[x]--;
				st[y]--;
				tmp+=dfs(st[0],st[1],st[2],st[3],st[4],st[5],st[6],st[7],st[8]);
				st[x]++;
				st[y]++;
			}
	if(cnt!=0)
		dp[a][b][c][d][e][f][g][h][i]=tmp/cnt;
	vis[a][b][c][d][e][f][g][h][i]=1;
	return dp[a][b][c][d][e][f][g][h][i];
}

int main()
{
	for(;;)
	{
		for(int i=0;i<9;i++)
			for(int j=0;j<4;j++)
				if(scanf("%s",str[i][j])==EOF)
					return 0;
		memset(vis,0,sizeof vis);
		memset(dp,0,sizeof dp);
		vis[0][0][0][0][0][0][0][0][0]=1;
		dp[0][0][0][0][0][0][0][0][0]=1;
		printf("%.6f\n",dfs(4,4,4,4,4,4,4,4,4));
	}
	
	return 0;
}
