#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
#define MAXN 505
#define check(a,b) (a>0&&b>0&&a<=N&&b<=M)
int N,M,step[MAXN][MAXN][3];
char map[MAXN][MAXN];
struct state{int x,y,d;}start,goal;
int BFS()
{
	memset(step,0x7F,sizeof step);
	queue<state>Q;
	step[start.x][start.y][start.d]=0;
	Q.push(start);
	while(!Q.empty())
	{
		state t=Q.front(),tt;
		Q.pop();
		switch(t.d)
		{
			case 0:
				tt=t;tt.y-=2;tt.d=2;
				if(check(tt.x,tt.y)&&map[tt.x][tt.y]!='#'&&map[tt.x][tt.y+1]!='#'&&step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
				{
					step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
					if(memcmp(&tt,&goal,sizeof(state))==0)return step[tt.x][tt.y][tt.d];
					Q.push(tt);
				};
				tt=t;tt.x-=2;tt.d=1;
				if(check(tt.x,tt.y)&&map[tt.x][tt.y]!='#'&&map[tt.x+1][tt.y]!='#'&&step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
				{
					step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
					if(memcmp(&tt,&goal,sizeof(state))==0)return step[tt.x][tt.y][tt.d];
					Q.push(tt);
				}
				tt=t;tt.y+=1;tt.d=2;
				if(check(tt.x,tt.y)&&map[tt.x][tt.y]!='#'&&map[tt.x][tt.y+1]!='#'&&step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
				{
					step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
					if(memcmp(&tt,&goal,sizeof(state))==0)return step[tt.x][tt.y][tt.d];
					Q.push(tt);
				}
				tt=t;tt.x+=1;tt.d=1;
				if(check(tt.x,tt.y)&&map[tt.x][tt.y]!='#'&&map[tt.x+1][tt.y]!='#'&&step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
				{
					step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
					if(memcmp(&tt,&goal,sizeof(state))==0)return step[tt.x][tt.y][tt.d];
					Q.push(tt);
				}
				break;
			case 1:
				tt=t;tt.x-=1;tt.d=0;
				if(check(tt.x,tt.y)&&map[tt.x][tt.y]!='#'&&map[tt.x][tt.y]!='E'&&step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
				{
					step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
					if(memcmp(&tt,&goal,sizeof(state))==0)return step[tt.x][tt.y][tt.d];
					Q.push(tt);
				}
				tt=t;tt.x+=2;tt.d=0;
				if(check(tt.x,tt.y)&&map[tt.x][tt.y]!='#'&&map[tt.x][tt.y]!='E'&&step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
				{
					step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
					if(memcmp(&tt,&goal,sizeof(state))==0)return step[tt.x][tt.y][tt.d];
					Q.push(tt);
				}
				tt=t;tt.y-=1;
				if(check(tt.x,tt.y)&&map[tt.x][tt.y]!='#'&&map[tt.x+1][tt.y]!='#'&&step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
				{
					step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
					if(memcmp(&tt,&goal,sizeof(state))==0)return step[tt.x][tt.y][tt.d];
					Q.push(tt);
				}
				tt=t;tt.y+=1;
				if(check(tt.x,tt.y)&&map[tt.x][tt.y]!='#'&&map[tt.x+1][tt.y]!='#'&&step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
				{
					step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
					if(memcmp(&tt,&goal,sizeof(state))==0)return step[tt.x][tt.y][tt.d];
					Q.push(tt);
				}
				break;
			case 2:
				tt=t;tt.y-=1;tt.d=0;
				if(check(tt.x,tt.y)&&map[tt.x][tt.y]!='#'&&map[tt.x][tt.y]!='E'&&step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
				{
					step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
					if(memcmp(&tt,&goal,sizeof(state))==0)return step[tt.x][tt.y][tt.d];
					Q.push(tt);
				}
				tt=t;tt.y+=2;tt.d=0;
				if(check(tt.x,tt.y)&&map[tt.x][tt.y]!='#'&&map[tt.x][tt.y]!='E'&&step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
				{
					step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
					if(memcmp(&tt,&goal,sizeof(state))==0)return step[tt.x][tt.y][tt.d];
					Q.push(tt);
				}
				tt=t;tt.x-=1;
				if(check(tt.x,tt.y)&&map[tt.x][tt.y]!='#'&&map[tt.x][tt.y+1]!='#'&&step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
				{
					step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
					if(memcmp(&tt,&goal,sizeof(state))==0)return step[tt.x][tt.y][tt.d];
					Q.push(tt);
				}
				tt=t;tt.x+=1;
				if(check(tt.x,tt.y)&&map[tt.x][tt.y]!='#'&&map[tt.x][tt.y+1]!='#'&&step[tt.x][tt.y][tt.d]>step[t.x][t.y][t.d]+1)
				{
					step[tt.x][tt.y][tt.d]=step[t.x][t.y][t.d]+1;
					if(memcmp(&tt,&goal,sizeof(state))==0)return step[tt.x][tt.y][tt.d];
					Q.push(tt);
				}
				break;
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
		for(int i=1,f=0;i<=N;i++)
		{
			scanf("%s",map[i]+1);
			for(int j=1;j<=M;j++)
			{
				if(map[i][j]=='O')
				{goal.x=i;goal.y=j;goal.d=0;}
				if(map[i][j]=='X'&&!f)
				{f=1;start.x=i;start.y=j;start.d=0;}
				if(map[i][j]=='X'&&f)
				{if(map[i-1][j]=='X')start.d=1;if(map[i][j-1]=='X')start.d=2;}
			}
		}
		int ans=BFS();
		if(ans==-1)
			printf("Impossible\n");
		else
			printf("%d\n",ans);
	}
	return 0;
}
