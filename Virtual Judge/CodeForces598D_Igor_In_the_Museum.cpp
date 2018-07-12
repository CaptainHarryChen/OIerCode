#include<cstdio>
#include<queue>
#include<stack>
using namespace std;
const int MAXN=1005;
const int dir[4][2]={{1,0},{0,1},{0,-1},{-1,0}};

int n,m,K;
char str[MAXN][MAXN];
int ans[MAXN][MAXN];
bool vis[MAXN][MAXN];

queue<int> Q;
int stk[MAXN*MAXN],tp;
void BFS(int sx,int sy)
{
	tp=0;
	int res=0;
	Q.push((sx-1)*m+sy);
	stk[++tp]=(sx-1)*m+sy;
	vis[sx][sy]=true;
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		int x=(u-1)/m+1;
		int y=(u-1)%m+1;
		for(int d=0;d<4;d++)
		{
			int tx=x+dir[d][0],ty=y+dir[d][1];
			if(tx<=0&&ty<=0&&tx>n&&ty>m)
				continue;
			if(str[tx][ty]=='*')
				res++;
			if(str[tx][ty]=='.'&&!vis[tx][ty])
			{
				Q.push((tx-1)*m+ty);
				stk[++tp]=(tx-1)*m+ty;
				vis[tx][ty]=true;
			}
		}
	}
	while(tp--)
	{
		int u=stk[tp+1];
		int x=(u-1)/m+1;
		int y=(u-1)%m+1;
		ans[x][y]=res;
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=n;i++)
		scanf("%s",str[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(str[i][j]=='.'&&ans[i][j]==0)
				BFS(i,j);
				
	while(K--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",ans[x][y]);
	}
	
	return 0;
}
