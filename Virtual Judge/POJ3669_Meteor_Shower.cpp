#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define MAXM 50005
#define MAXX 305
#define inside(x,y) (x>=0&&y>=0)
#define encode(x,y) (x*MAXX+y)
#define decodex(s) (s/MAXX)
#define decodey(s) (s%MAXX)
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int des[MAXX][MAXX];
int step[MAXX][MAXX];
queue<int>Q;
int main()
{
	int M;
	scanf("%d",&M);
	memset(des,0x7F,sizeof des);
	for(int i=1,x,y,t,tx,ty;i<=M;i++)
	{
		scanf("%d%d%d",&x,&y,&t);
		des[x][y]=min(des[x][y],t);
		for(int d=0;d<4;d++)
		{
			tx=x+dir[d][0];
			ty=y+dir[d][1];
			if(inside(tx,ty))
				des[tx][ty]=min(des[tx][ty],t);
		}
	}
	if(des[0][0]==0x7F7F7F7F)
	{
		printf("0\n");
		return 0;
	}
	memset(step,-1,sizeof step);
	Q.push(0);
	step[0][0]=0;
	int s,x,y,tx,ty;
	while(!Q.empty())
	{
		s=Q.front();Q.pop();
		x=decodex(s);
		y=decodey(s);
		for(int d=0;d<4;d++)
		{
			tx=x+dir[d][0];
			ty=y+dir[d][1];
			if(!inside(tx,ty)
				||step[tx][ty]!=-1
				||step[x][y]+1>=des[tx][ty])
				continue;
			step[tx][ty]=step[x][y]+1;
			if(des[tx][ty]==0x7F7F7F7F)
			{
				printf("%d\n",step[tx][ty]);
				return 0;
			}
			Q.push(encode(tx,ty));
		}
	}
	printf("-1\n");
	return 0;
}
