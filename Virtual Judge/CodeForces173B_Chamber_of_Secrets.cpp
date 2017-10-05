#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=1005;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
struct State
{
	int x,y,d,val;
	State(){}
	State(int _x,int _y,int _d,int _val)
	{x=_x;y=_y;d=_d;val=_val;}
	bool operator > (const State &t)const
	{return val>t.val;}
};
int n,m;
bool check(int x,int y)
{return x>0&&y>0&&x<=n&&y<=m;}
char map[MAXN][MAXN];
priority_queue<State,vector<State>,greater<State> >Q;
bool vis[MAXN][MAXN][4];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",map[i]+1);
	for(int j=m;j>=1;j--)
		if(map[n][j]=='#')
		{
			Q.push(State(n,j,3,0));
			vis[n][j][3]=true;
			break;
		}
	if(Q.empty())
	{
		puts("-1");
		return 0;
	}
	State t;
	while(!Q.empty())
	{
		t=Q.top();Q.pop();
		for(int nd=0;nd<4;nd++)
			if(nd!=(t.d+2)%4)
			{
				int nx=t.x,ny=t.y;
				do
				{
					nx+=dir[nd][0];
					ny+=dir[nd][1];
					if(nx==1&&ny==0)
					{
						printf("%d\n",t.val+(nd!=t.d));
						return 0;
					}
				}while(check(nx,ny)&&map[nx][ny]!='#');
				if(map[nx][ny]=='#'&&!vis[nx][ny][nd])
				{
					vis[nx][ny][nd]=true;
					Q.push(State(nx,ny,nd,t.val+(nd!=t.d)));
				}
			}
	}
	puts("-1");
	return 0;
}
