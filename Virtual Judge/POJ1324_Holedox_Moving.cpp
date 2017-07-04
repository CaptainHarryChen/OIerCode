#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
#define MAXN 30
#define check(a,b) (a>0&&b>0&&a<=N&&b<=M)
const int dd[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
int N,M,L,step[MAXN][MAXN][(1<<14)+10];
bool map[MAXN][MAXN];
struct state{int x,y,body;}start;
int BFS()
{
	if(start.x==1&&start.y==1)
		return 0;
	queue<state>Q;
	Q.push(start);
	memset(step,0x7F,sizeof step);
	step[start.x][start.y][start.body]=0;
	while(!Q.empty())
	{
		state t=Q.front(),tt;
		Q.pop();
		for(int i=0;i<4;i++)
		{
			tt.x=t.x+dd[i][0],tt.y=t.y+dd[i][1];
			if(!check(tt.x,tt.y)||map[tt.x][tt.y])continue;
			int kx=t.x,ky=t.y,kb=t.body,flag=1;
			for(int k=2;k<=L;k++)
			{
				if(tt.x==kx&&tt.y==ky)
				{flag=0;break;}
				kx+=dd[kb&3][0],ky+=dd[kb&3][1];
				kb>>=2;
			}
			if(!flag||(tt.x==kx&&tt.y==ky))continue;
			tt.body=((t.body<<2)+(i+2)%4)&((1<<((L-1)*2))-1);
			if(step[tt.x][tt.y][tt.body]>step[t.x][t.y][t.body]+1)
			{
				step[tt.x][tt.y][tt.body]=step[t.x][t.y][t.body]+1;
				if(tt.x==1&&tt.y==1)
					return step[tt.x][tt.y][tt.body];
				Q.push(tt);
			}
		}
	}
	return -1;
}
int main()
{
	for(int T=1;;T++)
	{
		scanf("%d%d%d",&N,&M,&L);
		if(!N&&!M&&!L)break;
		int k,x,y,a,b;
		scanf("%d%d",&start.x,&start.y);
		a=start.x,b=start.y;start.body=0;
		for(int i=2;i<=L;i++)
		{
			scanf("%d%d",&x,&y);
			if(y==b+1){start.body+=(3<<((i-2)*2));}
			if(x==a+1){start.body+=(2<<((i-2)*2));}
			if(y==b-1){start.body+=(1<<((i-2)*2));}
			a=x;b=y;
		}
		scanf("%d",&k);
		memset(map,0,sizeof map);
		for(int i=1;i<=k;i++)
		{
			scanf("%d%d",&x,&y);
			map[x][y]=1;
		}
		printf("Case %d: ",T);
		printf("%d\n",BFS());
	}
	return 0;
}
