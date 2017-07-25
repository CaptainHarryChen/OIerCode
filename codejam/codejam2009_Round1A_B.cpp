#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=23;
const int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int N,M,dis[MAXN][MAXN][4];
int S[MAXN][MAXN],W[MAXN][MAXN],T[MAXN][MAXN];
struct Pos
{
	int x,y,d;
	Pos(){}
	Pos(int _x,int _y,int _d)
	{
		x=_x;y=_y;d=_d;
	}
	bool operator < (const Pos &t)const
	{
		return x<t.x;
	}
};
int wait(int t,int x,int y,int mode)
{
	t=(t-T[x][y])%(S[x][y]+W[x][y]);
	if(mode==0)
		return (t<S[x][y])?0:(S[x][y]+W[x][y]-t);
	return (t>=S[x][y])?0:(S[x][y]-t);
}
typedef pair<int,Pos> state;
priority_queue<state,vector<state>,greater<state> > Q;
void Dijkstra()
{
	memset(dis,0x3F,sizeof dis);
	dis[N][1][3]=0;
	Q.push(make_pair(0,Pos(N,1,3)));
	while(!Q.empty())
	{
		state t=Q.top();Q.pop();
		Pos tp=t.second,ttp;
		if(dis[tp.x][tp.y][tp.d]<t.first)
			continue;
		ttp=tp;
		ttp.x+=dir[ttp.d][0];
		ttp.y+=dir[ttp.d][1];
		ttp.d=(ttp.d+1)%4;
		if(ttp.x>0&&ttp.y>0&&ttp.x<=N&&ttp.y<=M&&dis[tp.x][tp.y][tp.d]+2<dis[ttp.x][ttp.y][ttp.d])
		{
			dis[ttp.x][ttp.y][ttp.d]=dis[tp.x][tp.y][tp.d]+2;
			Q.push(make_pair(dis[ttp.x][ttp.y][ttp.d],ttp));
		}
		ttp=tp;
		ttp.x+=dir[(ttp.d+1)%4][0];
		ttp.y+=dir[(ttp.d+1)%4][1];
		ttp.d=(ttp.d+3)%4;
		if(ttp.x>0&&ttp.y>0&&ttp.x<=N&&ttp.y<=M&&dis[tp.x][tp.y][tp.d]+2<dis[ttp.x][ttp.y][ttp.d])
		{
			dis[ttp.x][ttp.y][ttp.d]=dis[tp.x][tp.y][tp.d]+2;
			Q.push(make_pair(dis[ttp.x][ttp.y][ttp.d],ttp));
		}
		ttp=tp;
		ttp.d=(ttp.d+1)%4;
		if(ttp.x>0&&ttp.y>0&&ttp.x<=N&&ttp.y<=M&&dis[tp.x][tp.y][tp.d]+wait(dis[tp.x][tp.y][tp.d],tp.x,tp.y,ttp.d%2)+1<dis[ttp.x][ttp.y][ttp.d])
		{
			dis[ttp.x][ttp.y][ttp.d]=dis[tp.x][tp.y][tp.d]+wait(dis[tp.x][tp.y][tp.d],tp.x,tp.y,ttp.d%2)+1;
			Q.push(make_pair(dis[ttp.x][ttp.y][ttp.d],ttp));
		}
		ttp=tp;
		ttp.d=(ttp.d+3)%4;
		if(ttp.x>0&&ttp.y>0&&ttp.x<=N&&ttp.y<=M&&dis[tp.x][tp.y][tp.d]+wait(dis[tp.x][tp.y][tp.d],tp.x,tp.y,(ttp.d+1)%2)+1<dis[ttp.x][ttp.y][ttp.d])
		{
			dis[ttp.x][ttp.y][ttp.d]=dis[tp.x][tp.y][tp.d]+wait(dis[tp.x][tp.y][tp.d],tp.x,tp.y,(ttp.d+1)%2)+1;
			Q.push(make_pair(dis[ttp.x][ttp.y][ttp.d],ttp));
		}
	}
}
int main()
{
	int C;
	scanf("%d",&C);
	for(int Case=1;Case<=C;Case++)
	{
		scanf("%d%d",&N,&M);
		for(int i=1;i<=N;i++)
			for(int j=1;j<=M;j++)
			{
				scanf("%d%d%d",S[i]+j,W[i]+j,T[i]+j);
				T[i][j]%=S[i][j]+W[i][j];
				if(T[i][j]>0)T[i][j]-=S[i][j]+W[i][j];
			}
		Dijkstra();
		printf("Case #%d: %d\n",Case,dis[1][M][1]);
	}
	return 0;
}
