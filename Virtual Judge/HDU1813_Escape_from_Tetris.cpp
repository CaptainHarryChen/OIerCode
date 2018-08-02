#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=10,MAXS=50;
const int dir[4][2]={{0,1},{-1,0},{1,0},{0,-1}};
const char str_dir[4][6]={"east","north","south","west"};

int n;
int board[MAXN][MAXN],dis[MAXN][MAXN];

inline bool check(int x,int y)
{return x>0&&y>0&&x<=n&&y<=n;}
inline int encode(int x,int y)
{return (x-1)*n+y;}
inline void decode(int c,int &x,int &y)
{x=(c-1)/n+1;y=(c-1)%n+1;}

inline void InitDis()
{
	static queue<int> Q;
	memset(dis,0x3F,sizeof dis);
	for(int i=1;i<=n;i++)
	{
		if(board[1][i]==0)
			dis[1][i]=0,Q.push(encode(1,i));
		if(board[n][i]==0)
			dis[n][i]=0,Q.push(encode(n,i));
		if(board[i][1]==0)
			dis[i][1]=0,Q.push(encode(i,1));
		if(board[i][n]==0)
			dis[i][n]=0,Q.push(encode(i,n));
	}
	while(!Q.empty())
	{
		int x,y,u=Q.front();
		Q.pop();
		decode(u,x,y);
		for(int d=0;d<4;d++)
		{
			int tx=x+dir[d][0],ty=y+dir[d][1];
			if(!check(tx,ty)||board[tx][ty]||dis[tx][ty]!=0x3F3F3F3F)
				continue;
			dis[tx][ty]=dis[x][y]+1;
			Q.push(encode(tx,ty));
		}
	}
}

int stk[MAXS],top;
int path[MAXS];

bool dfs(int step,int lim)
{
	int g=0;
	for(int i=1;i<=top;i++)
	{
		int x,y;
		decode(stk[i],x,y);
		g=max(g,dis[x][y]);
	}
	if(step+g>lim)
		return false;
	if(step==lim)
		return true;
	
	int tmp[MAXS];
	memcpy(tmp,stk,sizeof(int)*(top+1));
	for(int d=0;d<4;d++)
	{
		for(int i=1;i<=top;i++)
		{
			int x,y;
			decode(tmp[i],x,y);
			if(x==1||y==1||x==n||y==n)
				continue;
			int tx=x+dir[d][0],ty=y+dir[d][1];
			if(!check(tx,ty)||board[tx][ty])
				continue;
			stk[i]=encode(tx,ty);
			if(tx==1||ty==1||tx==n||ty==n)
				continue;
		}
		path[step+1]=d;
		if(dfs(step+1,lim))
			return true;
		for(int i=1;i<=top;i++)
			stk[i]=tmp[i];
	}
	
	return false;
}

void Solve()
{
	top=0;
	int ans=0;
	for(int i=2;i<n;i++)
		for(int j=2;j<n;j++)
			if(board[i][j]==0)
			{
				stk[++top]=encode(i,j);
				ans=max(ans,dis[i][j]);
			}
	while(!dfs(0,ans))
		ans++;
	for(int i=1;i<=ans;i++)
		puts(str_dir[path[i]]);
}

int main()
{
	bool flag=0;
	while(scanf("%d",&n)!=EOF)
	{
		if(flag)
			puts("");
		flag=true;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				scanf("%1d",&board[i][j]);
		InitDis();
		Solve();
	}
	
	return 0;
}
