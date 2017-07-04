#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXC=60,MAXR=160,MAXS=60000;
int N,M,K;
bool map[2][MAXR][MAXC];
int dp[2][MAXS];
int ans;
void DFS(int row,int col,int s1,int s2,int num)
{
	if(col>M)
	{
		dp[row%2][s1]=max(dp[row%2][s1],dp[(row-1)%2][s2]+num);
		ans=max(ans,dp[row%2][s1]);
		return;
	}
	if(col+1<=M&&!map[0][row][col]&&row>2)
		DFS(row,col+2,s1*9+8,s2*9,num+1);
	if(col+2<=M&&!map[1][row][col]&&row>1)
		DFS(row,col+3,s1*27+26,s2*27+13,num+1);
	DFS(row,col+1,s1*3+1,s2*3+2,num);
	DFS(row,col+1,s1*3,s2*3+1,num);
	DFS(row,col+1,s1*3+2,s2*3+2,num);
}
int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		scanf("%d%d%d",&N,&M,&K);
		memset(map,0,sizeof map);
		for(int k=1,a,b;k<=K;k++)
		{
			scanf("%d%d",&a,&b);
			for(int i=0;i<3&&a+i<=N;i++)
				for(int j=0;j<2&&b-j>0;j++)
					map[0][a+i][b-j]=1;
			for(int i=0;i<2&&a+i<=N;i++)
				for(int j=0;j<3&&b-j>0;j++)
					map[1][a+i][b-j]=1;
		}
		memset(dp,0,sizeof dp);
		ans=0;
		for(int i=1;i<=N;i++)
			DFS(i,1,0,0,0);
		printf("%d\n",ans);
	}
	return 0;
}
