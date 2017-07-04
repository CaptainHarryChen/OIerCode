#include<cstdio>
#include<map>
#include<queue>
using namespace std;
const int dir[4]={-4,1,4,-1};
struct state
{
	int board[8];
	bool operator < (const state &t)const
	{
		for(int i=0;i<8;i++)
			if(board[i]!=t.board[i])
				return board[i]<t.board[i];
		return 0;
	}
	bool operator != (const state &t)const
	{
		for(int i=0;i<8;i++)
			if(board[i]!=t.board[i])
				return 1;
		return 0;
	}
};
map<state,int>step;
queue<state>Q;
void BFS()
{
	state st={{0,1,2,3,4,5,6,7}},t,tt;
	int pos,tpos;
	Q.push(st);
	while(!Q.empty())
	{
		t=Q.front();
		Q.pop();
		for(pos=0;pos<8&&t.board[pos]!=0;pos++);
		for(int d=0;d<4;d++)
		{
			tpos=pos+dir[d];
			if(tpos<0||tpos>=8)continue;
			if(d==1&&pos==3)continue;
			if(d==3&&pos==4)continue;
			tt=t;
			swap(tt.board[pos],tt.board[tpos]);
			if(tt!=st&&step[tt]==0)
			{
				step[tt]=step[t]+1;
				Q.push(tt);
			}
		}
	}
}
int main()
{
	BFS();
	state tmp;
	while(~scanf("%d",tmp.board))
	{
		for(int i=1;i<8;i++)
			scanf("%d",tmp.board+i);
		printf("%d\n",step[tmp]);
	}
	return 0;
}
