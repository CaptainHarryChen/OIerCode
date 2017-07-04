#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
#define MAXN 53
#define check(a,b) (a>0&&b>0&&a<N&&b<M)
const int dd[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int N,M,step[MAXN][MAXN][4];
bool map[MAXN][MAXN];
struct state{int x,y,d;}start,goal;
int BFS()
{
	if(start.x==goal.x&&start.y==goal.y)
		return 0;
	memset(step,127,sizeof step);
	queue<state>Q;
	Q.push(start);
	step[start.x][start.y][start.d]=0;
	while(!Q.empty())
	{
		state t=Q.front();
		Q.pop();
		state tt;
		for(int i=1;i<=3;i++)
		{
			tt=t;
			tt.x+=i*dd[t.d][0];tt.y+=i*dd[t.d][1];
			if(map[tt.x][tt.y])break;
			if(check(tt.x,tt.y)&&step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
			{
				step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
				if(tt.x==goal.x&&tt.y==goal.y)
					return step[tt.x][tt.y][tt.d];
				Q.push(tt);
			}
		}
		tt=t;
		tt.d=(t.d+1)%4;
		if(step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
		{
			step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
			if(tt.x==goal.x&&tt.y==goal.y)
				return step[tt.x][tt.y][tt.d];
			Q.push(tt);
		}
		tt=t;
		tt.d=(t.d-1+4)%4;
		if(step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
		{
			step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
			if(tt.x==goal.x&&tt.y==goal.y)
				return step[tt.x][tt.y][tt.d];
			Q.push(tt);
		}
	}
	return -1;
}
int main()
{
	while(1)
	{
		scanf("%d%d",&N,&M);
		if(!N&&!M)break;
		memset(map,0,sizeof map);
		for(int i=1;i<=N;i++)
			for(int j=1,x;j<=M;j++)
			{
				scanf("%d",&x);
				if(x)
					map[i-1][j-1]=map[i][j-1]=map[i-1][j]=map[i][j]=1;
			}
		scanf("%d%d%d%d",&start.x,&start.y,&goal.x,&goal.y);
		char str[10];
		scanf("%s",str);
		switch(str[0])
		{
			case 'n':start.d=0;break;
			case 'e':start.d=1;break;
			case 's':start.d=2;break;
			case 'w':start.d=3;break;
		}
		printf("%d\n",BFS());
	}
	return 0;
}
