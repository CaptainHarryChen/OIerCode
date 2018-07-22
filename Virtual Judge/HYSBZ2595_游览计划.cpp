#include<cstring>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=12,MAXS=1030,INF=0x3F3F3F3F;
const int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};

int n,m;
int dp[MAXN][MAXN][MAXS],pref[MAXN][MAXN][MAXS][3];
bool use[MAXN][MAXN];
int A[MAXN][MAXN],id[MAXN][MAXN];
int sp;
pair<int,int> spot[MAXN];
queue< pair<int,int> > Q;
bool inq[MAXN][MAXN];

void dfs(int i,int j,int s)
{
	use[i][j]=true;
	int ti=pref[i][j][s][0],tj=pref[i][j][s][1],ts=pref[i][j][s][2];
	if(ti==0&&tj==0&&ts==0)
		return;
	dfs(ti,tj,ts);
	if(ts!=s)
		dfs(ti,tj,s^ts);
}

int main()
{
	memset(dp,0x3F,sizeof dp);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&A[i][j]);
			if(A[i][j]==0)
			{
				spot[++sp]=(make_pair(i,j));
				id[i][j]=sp;
				dp[i][j][(1<<(sp-1))]=0;
			}
		}
	for(int s=1;s<(1<<sp);s++)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				for(int ts=(s-1)&s;ts>0;ts=(ts-1)&s)
					if(dp[i][j][ts]<INF&&dp[i][j][s^ts]<INF)
					{
						int tmp=dp[i][j][ts]+dp[i][j][s^ts]-A[i][j];
						if(dp[i][j][s]>tmp)
						{
							dp[i][j][s]=tmp;
							pref[i][j][s][0]=i;
							pref[i][j][s][1]=j;
							pref[i][j][s][2]=ts;
						}
					}
				if(dp[i][j][s]<INF)
				{
					Q.push(make_pair(i,j));
					inq[i][j]=true;
				}
			}
		while(!Q.empty())
		{
			int x=Q.front().first;
			int y=Q.front().second;
			Q.pop();
			inq[x][y]=false;
			for(int d=0;d<4;d++)
			{
				int tx=x+dir[d][0],ty=y+dir[d][1];
				if(tx<=0||ty<=0||tx>n||ty>m)
					continue;
				if(dp[tx][ty][s]>dp[x][y][s]+A[tx][ty])
				{
					dp[tx][ty][s]=dp[x][y][s]+A[tx][ty];
					pref[tx][ty][s][0]=x;
					pref[tx][ty][s][1]=y;
					pref[tx][ty][s][2]=s;
					if(!inq[tx][ty])
					{
						Q.push(make_pair(tx,ty));
						inq[tx][ty]=true;
					}
				}
			}
		}
		/*for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				printf("dp[%d][%d][%d]=%d\n",i,j,s,dp[i][j][s]);
		puts("");*/
	}
	printf("%d\n",dp[spot[1].first][spot[1].second][(1<<sp)-1]);
	dfs(spot[1].first,spot[1].second,(1<<sp)-1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(A[i][j]==0)
				putchar('x');
			else if(use[i][j])
				putchar('o');
			else
				putchar('_');
		}
		puts("");
	}
	return 0;
}
