#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define ZERO 11
#define MAXN 22
#define right(a,b) (a+ZERO>=0&&b+ZERO>=0&&a+ZERO<=MAXN&&b+ZERO<=MAXN)
const int dd[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int n1,n2,n3,l1,r1,u1,d1,l2,r2,u2,d2,l3,r3,u3,d3;
struct XY
{
	int x,y;
}b1[85],b2[85],b3[85];
bool vis[MAXN+1][MAXN+1][MAXN+1][MAXN+1];
bool map[MAXN+1][MAXN+1];
void input()
{
	scanf("%d%d%d",&n1,&n2,&n3);
	l1=d1=l2=d2=l3=d3=100;
	r1=u1=r2=u2=r3=u3=-100;
	for(int i=1;i<=n1;i++)
	{
		scanf("%d%d",&b1[i].x,&b1[i].y);
		l1=min(l1,b1[i].x);
		r1=max(r1,b1[i].x);
		u1=max(u1,b1[i].y);
		d1=min(d1,b1[i].y);
	}
	for(int i=1;i<=n2;i++)
	{
		scanf("%d%d",&b2[i].x,&b2[i].y);
		l2=min(l2,b2[i].x);
		r2=max(r2,b2[i].x);
		u2=max(u2,b2[i].y);
		d2=min(d2,b2[i].y);
	}
	for(int i=1;i<=n3;i++)
	{
		scanf("%d%d",&b3[i].x,&b3[i].y);
		l3=min(l3,b3[i].x);
		r3=max(r3,b3[i].x);
		u3=max(u3,b3[i].y);
		d3=min(d3,b3[i].y);
	}
}
bool mark(XY a,XY b)
{
	if(vis[a.x+ZERO][a.y+ZERO][b.x+ZERO][b.y+ZERO])return 0;
	vis[a.x+ZERO][a.y+ZERO][b.x+ZERO][b.y+ZERO]=1;
	return 1;
}
bool check(XY a,XY b,XY c)
{
	if(!right(b.x,b.y))return 0;
	if(!right(c.x,c.y))return 0;
	memset(map,0,sizeof map);
	for(int i=1;i<=n1;i++)
		map[b1[i].x+ZERO][b1[i].y+ZERO]=1;
	for(int i=1;i<=n2;i++)
		if(map[b2[i].x-b2[1].x+b.x+ZERO][b2[i].y-b2[1].y+b.y+ZERO])
			return 0;
		else
			map[b2[i].x-b2[1].x+b.x+ZERO][b2[i].y-b2[1].y+b.y+ZERO]=1;
	for(int i=1;i<=n3;i++)
		if(map[b3[i].x-b3[1].x+c.x+ZERO][b3[i].y-b3[1].y+c.y+ZERO])
			return 0;
		else
			map[b3[i].x-b3[1].x+c.x+ZERO][b3[i].y-b3[1].y+c.y+ZERO]=1;
	return 1;
}
bool finish(XY a,XY b,XY c)
{
	bool f1,f2,f3;
	f1=(a.x+l1-b1[1].x>b.x+r2-b2[1].x)||(a.x+r1-b1[1].x<b.x+l2-b2[1].x)
	||(a.y+d1-b1[1].y>b.y+u2-b2[1].y)||(a.y+u1-b1[1].y<b.y+d2-b2[1].y);
	f2=(b.x+l2-b2[1].x>c.x+r3-b3[1].x)||(b.x+r2-b2[1].x<c.x+l3-b3[1].x)
	||(b.y+d2-b2[1].y>c.y+u3-b3[1].y)||(b.y+u2-b2[1].y<c.y+d3-b3[1].y);
	f3=(a.x+l1-b1[1].x>c.x+r3-b3[1].x)||(a.x+r1-b1[1].x<c.x+l3-b3[1].x)
	||(a.y+d1-b1[1].y>c.y+u3-b3[1].y)||(a.y+u1-b1[1].y<c.y+d3-b3[1].y);
	return f1&&f2&&f3;
}
int dfs(XY b,XY c)
{
	XY t;
	for(int i=0;i<4;i++)
	{
		t.x=b.x+dd[i][0];t.y=b.y+dd[i][1];
		if(check(b1[1],t,c))
		{
			if(finish(b1[1],t,c))
				return 1;
			if(!mark(t,c))
				continue;
			if(dfs(t,c))
				return 1;
		}
	}
	for(int i=0;i<4;i++)
	{
		t.x=c.x+dd[i][0];t.y=c.y+dd[i][1];
		if(check(b1[1],b,t))
		{
			if(finish(b1[1],b,t))
				return 1;
			if(!mark(b,t))
				continue;
			if(dfs(b,t))
				return 1;
		}
	}
	XY t1,t2;
	for(int i=0;i<4;i++)
	{
		t1.x=b.x+dd[i][0];t1.y=b.y+dd[i][1];
		t2.x=c.x+dd[i][0];t2.y=c.y+dd[i][1];
		if(check(b1[1],t1,t2))
		{
			if(finish(b1[1],t1,t2))
				return 1;
			if(!mark(t1,t2))
				continue;
			if(dfs(t1,t2))
				return 1;
		}
	}
	return 0;
}
int main()
{
	input();
	mark(b2[1],b3[1]);
	printf("%d\n",dfs(b2[1],b3[1]));
	return 0;
}
