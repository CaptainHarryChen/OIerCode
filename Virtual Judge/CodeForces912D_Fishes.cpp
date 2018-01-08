#include<cstdio>
#include<queue>
#include<vector>
#include<map>
using namespace std;
const int MAXN=100005;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int n,m,r,k;
struct pos
{
	int x,y;
	double v;
	pos(){}
	pos(int _x,int _y)
	{
		x=_x;y=_y;
		int x1,y1,x2,y2;
		x1=max(r-(m-x),1);
		y1=max(r-(n-y),1);
		x2=min(x,r);
		y2=min(y,r);
		v=max(0.0,1.0*(x2-x1+1)*(y2-y1+1));
	}
	bool check()
	{return x>0&&y>0&&x<=m&&y<=n;}
	bool operator < (const pos& t)const
	{return v<t.v;}
};
map<pair<int,int>,bool> vis;
priority_queue<pos> Q;
int main()
{
	scanf("%d%d%d%d",&n,&m,&r,&k);
	double ans=0.0;
	pos t((m+1)/2,(n+1)/2),tt;
	vis[make_pair(t.x,t.y)]=true;
	Q.push(t);
	while(!Q.empty()&&k)
	{
		t=Q.top();
		Q.pop();
		ans+=t.v;
		k--;
		if(k<=0)break;
		for(int d=0;d<4;d++)
		{
			tt=pos(t.x+dir[d][0],t.y+dir[d][1]);
			if(tt.check()&&!vis[make_pair(tt.x,tt.y)])
			{
				vis[make_pair(tt.x,tt.y)]=true;
				Q.push(tt);
			}
		}
	}
	printf("%.12lf\n",ans/(1.0*(n-r+1)*(m-r+1)));
	return 0;
}
