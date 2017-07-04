#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
#define MAXN 35
#define ecode(a,b) ((a-1)*M+b)
#define get_x(s) ((s-1)/M+1)
#define get_y(s) ((s-1)%M+1)
const int dir[4][2]={{-1,0},{1,0},{0,1},{0,-1}};
int N,M,P,cnt;
bool map[MAXN][MAXN];
int state[MAXN][MAXN][5];
int step[MAXN*MAXN];
int dis[MAXN*MAXN*5];
bool vis[MAXN*MAXN*5];
struct Edge
{
	int u,w;
	Edge *next;
	Edge(){}
	Edge(int a,int b):u(a),w(b),next(NULL){}
}edge[MAXN*MAXN*5];
void add_edge();
void init();
void make_G();
int get_step(int,int,int,int);
void solve();
int SPFA(int,int);
int main()
{
	init();
	make_G();
	solve();
	return 0;
}
void add_edge(int a,int b,int w)
{
	Edge *p=new Edge(b,w);
	p->next=edge[a].next;
	edge[a].next=p;
}
void init()
{
	cnt=0;
	scanf("%d%d%d",&N,&M,&P);
	for(int i=1,a;i<=N;i++)
		for(int j=1;j<=M;j++)
		{
			scanf("%d",&a);
			map[i][j]=a;
			for(int k=0;k<4;k++)
				state[i][j][k]=++cnt;
		}
}
void make_G()
{
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++)
			if(map[i][j])
				for(int k=0;k<4;k++)
					if(map[i+dir[k][0]][j+dir[k][1]])
					{
						add_edge(state[i][j][k],state[i+dir[k][0]][j+dir[k][1]][k^1],1);
						for(int h=0;h<4;h++)
							if(k!=h&&map[i+dir[h][0]][j+dir[h][1]])
							{
								map[i][j]=0;
								int step=1+get_step(i+dir[k][0],j+dir[k][1],i+dir[h][0],j+dir[h][1]);
								if(step>=0)
									add_edge(state[i][j][k],state[i+dir[h][0]][j+dir[h][1]][h^1],step);
								map[i][j]=1;
							}
					}
}
int get_step(int sx,int sy,int gx,int gy)
{
	if(sx==gx&&sy==gy)return 0;
	memset(step,-1,sizeof step);
	queue<int>Q;
	Q.push(ecode(sx,sy));
	step[ecode(sx,sy)]=0;
	while(!Q.empty())
	{
		int t=Q.front();Q.pop();
		int tx=get_x(t),ty=get_y(t);
		for(int k=0;k<4;k++)
			if(map[tx+dir[k][0]][ty+dir[k][1]]&&step[ecode(tx+dir[k][0],ty+dir[k][1])]==-1)
			{
				if(tx+dir[k][0]==gx&&ty+dir[k][1]==gy)
					return step[t]+1;
				step[ecode(tx+dir[k][0],ty+dir[k][1])]=step[t]+1;
				Q.push(ecode(tx+dir[k][0],ty+dir[k][1]));
			}
	}
	return -100000;
}
void solve()
{
	int ex,ey,sx,sy,gx,gy;
	while(P--)
	{
		scanf("%d%d%d%d%d%d",&ex,&ey,&sx,&sy,&gx,&gy);
		if(sx==gx&&sy==gy)
		{printf("0\n");continue;}
		if(!map[ex][ey]||!map[sx][sy]||!map[gx][gy])
		{printf("-1\n");continue;}
		int S=++cnt,T=++cnt;
		map[sx][sy]=0;
		for(int k=0;k<4;k++)
			if(map[sx+dir[k][0]][sy+dir[k][1]])
			{
				int step=get_step(ex,ey,sx+dir[k][0],sy+dir[k][1]);
				if(step>=0)
					add_edge(S,state[sx][sy][k],step);
			}
		map[sx][sy]=1;
		for(int k=0;k<4;k++)
			if(map[gx+dir[k][0]][gy+dir[k][1]])
				add_edge(state[gx][gy][k],T,0);
		printf("%d\n",SPFA(S,T));
	}
}
int SPFA(int S,int T)
{
	if(S==T)
		return 0;
	memset(vis,0,sizeof vis);
	memset(dis,0x3F,sizeof dis);
	queue<int>Q;
	Q.push(S);
	vis[S]=1;
	dis[S]=0;
	while(!Q.empty())
	{
		int t=Q.front();
		Q.pop();vis[t]=0;
		for(Edge *p=edge[t].next;p;p=p->next)
			if(dis[p->u]>dis[t]+p->w)
			{
				dis[p->u]=dis[t]+p->w;
				if(!vis[p->u])
				{
					vis[p->u]=1;
					Q.push(p->u);
				}
			}
	}
	return dis[T]==0x3F3F3F3F?-1:dis[T];
}
