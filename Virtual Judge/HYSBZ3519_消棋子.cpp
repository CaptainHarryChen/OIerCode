#include<cstdio>
#include<set>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=100005;
int R,C,N;
struct Point
{
	int x,y;
	Point(){}
	Point(int _x,int _y):x(_x),y(_y){}
	void Read(){scanf("%d%d",&x,&y);}
	bool operator < (Point t)const
	{return x<t.x||(x==t.x&&y<t.y);}
}P[MAXN][2];
struct ID
{
	int pri,c,i;
	ID(){}
	ID(int _p,int _c,int _i):pri(_p),c(_c),i(_i){}
	bool operator < (ID t)const
	{return pri<t.pri;}
};
set<ID> row[MAXN],col[MAXN];
map<Point,bool> has;
void Read()
{
	scanf("%d%d",&R,&C);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		P[i][0].Read(),P[i][1].Read();
}
void Init()
{
	for(int i=1;i<=R;i++)row[i].clear();
	for(int i=1;i<=C;i++)col[i].clear();
	has.clear();
	for(int i=1;i<=N;i++)
	{
		has[P[i][0]]=1;
		has[P[i][1]]=1;
		row[P[i][0].x].insert(ID(P[i][0].y,i,0));
		row[P[i][1].x].insert(ID(P[i][1].y,i,1));
		col[P[i][0].y].insert(ID(P[i][0].x,i,0));
		col[P[i][1].y].insert(ID(P[i][1].x,i,1));
	}
}
void erase(int color)
{
	row[P[color][0].x].erase(ID(P[color][0].y,color,0));
	row[P[color][1].x].erase(ID(P[color][1].y,color,1));
	col[P[color][0].y].erase(ID(P[color][0].x,color,0));
	col[P[color][1].y].erase(ID(P[color][1].x,color,1));
	has[P[color][0]]=0;
	has[P[color][1]]=0;
}
void solve1()
{
	int M;
	scanf("%d",&M);
	int x,y;
	char d1,d2;
	set<ID>::iterator it;
	int color=-1,ans=0;
	for(int i=1;i<=M;i++)
	{
		scanf("%d %d %c %c",&x,&y,&d1,&d2);
		if(has[Point(x,y)])
			continue;
		color=-1;
		if(d1=='U'||d2=='U')
		{
			it=col[y].lower_bound(ID(x,0,0));
			if(it==col[y].begin())continue;
			it--;
			if(~color&&it->c!=color)
				continue;
			else if(~color&&it->c==color)
			{
				erase(color);
				ans++;
				continue;
			}
			else if(color==-1)
				color=it->c;
		}
		if(d1=='D'||d2=='D')
		{
			it=col[y].upper_bound(ID(x,0,0));
			if(it==col[y].end())continue;
			if(~color&&it->c!=color)
				continue;
			else if(~color&&it->c==color)
			{
				erase(color);
				ans++;
				continue;
			}
			else if(color==-1)
				color=it->c;
		}
		if(d1=='L'||d2=='L')
		{
			it=row[x].lower_bound(ID(y,0,0));
			if(it==row[x].begin())continue;
			it--;
			if(~color&&it->c!=color)
				continue;
			else if(~color&&it->c==color)
			{
				erase(color);
				ans++;
				continue;
			}
			else if(color==-1)
				color=it->c;
		}
		if(d1=='R'||d2=='R')
		{
			it=row[x].upper_bound(ID(y,0,0));
			if(it==row[x].end())continue;
			if(~color&&it->c!=color)
				continue;
			else if(~color&&it->c==color)
			{
				erase(color);
				ans++;
				continue;
			} 
			else if(color==-1)
				color=it->c;
		}
	}
	printf("%d\n",ans);
}
queue<int>Q;
int output[MAXN][4],cnt;
bool check(int color)
{
	if(P[color][0].x==P[color][1].x&&(P[color][0].y==P[color][1].y-1||P[color][0].y==P[color][1].y+1))return 0;
	if(P[color][0].y==P[color][1].y&&(P[color][0].x==P[color][1].x-1||P[color][0].x==P[color][1].x+1))return 0;
	set<ID>::iterator it;
	bool flag=1;
	int x1=P[color][0].x,x2=P[color][1].x,y1=P[color][0].y,y2=P[color][1].y;
	if(x1==x2)
	{
		it=row[x1].find(ID(y1,color,0));
		if(y1<y2)
		{
			it++;
			if(it!=row[x1].end()&&it->c==color)
			{
				cnt++;
				output[cnt][0]=x1;output[cnt][1]=y1+1;
				output[cnt][2]='L';output[cnt][3]='R';
				return 1;
			}
		}
		if(y2<y1&&it!=row[x1].begin())
		{
			it--;
			if(it->c==color)
			{
				cnt++;
				output[cnt][0]=x1;output[cnt][1]=y1-1;
				output[cnt][2]='L';output[cnt][3]='R';
				return 1;
			}
		}
		return 0;
	}
	if(y1==y2)
	{
		it=col[y1].find(ID(x1,color,0));
		if(x1<x2)
		{
			it++;
			if(it!=col[y1].end()&&it->c==color)
			{
				cnt++;
				output[cnt][0]=x1+1;output[cnt][1]=y1;
				output[cnt][2]='U';output[cnt][3]='D';
				return 1;
			}
		}
		if(x2<x1&&it!=col[y1].begin())
		{
			it--;
			if(it->c==color)
			{
				cnt++;
				output[cnt][0]=x1-1;output[cnt][1]=y1;
				output[cnt][2]='U';output[cnt][3]='D';
				return 1;
			}
		}
		return 0;
	}
	it=row[x1].find(ID(y1,color,0));
	if(y1<y2)
	{
		it++;
		if(it!=row[x1].end()&&it->pri<=y2)
			flag=0;
	}
	else if(y2<y1)
	{
		if(it!=row[x1].begin())
		{
			it--;
			if(it->pri>=y2)
				flag=0;
		}
	}
	if(flag)
	{
		it=col[y2].find(ID(x2,color,1));
		if(x2<x1)
		{
			it++;
			if(it!=col[y2].end()&&it->pri<=x1)
				flag=0;
		}
		else if(x1<x2)
		{
			if(it!=col[y2].begin())
			{
				it--;
				if(it->pri>=x1)
					flag=0;
			}
		}
	}
	if(flag)
	{
		cnt++;
		output[cnt][0]=x1;output[cnt][1]=y2;
		if(x1>x2)output[cnt][2]='U';
		else output[cnt][2]='D';
		if(y1>y2)output[cnt][3]='R';
		else output[cnt][3]='L';
		return 1;
	}
	flag=1;
	it=row[x2].find(ID(y2,color,1));
	if(y2<y1)
	{
		it++;
		if(it!=row[x2].end()&&it->pri<=y1)
			flag=0;
	}
	else if(y1<y2)
	{
		if(it!=row[x2].begin())
		{
			it--;
			if(it->pri>=y1)
				flag=0;
		}
	}
	if(flag)
	{
		it=col[y1].find(ID(x1,color,0));
		if(x1<x2)
		{
			it++;
			if(it!=col[y1].end()&&it->pri<=x2)
				flag=0;
		}
		else if(x2<x1)
		{
			if(it!=col[y1].begin())
			{
				it--;
				if(it->pri>=x2)
					flag=0;
			}
		}
	}
	if(flag)
	{
		cnt++;
		output[cnt][0]=x2;output[cnt][1]=y1;
		if(x1<x2)output[cnt][2]='U';
		else output[cnt][2]='D';
		if(y1<y2)output[cnt][3]='R';
		else output[cnt][3]='L';
		return 1;
	}
	return 0;
}
int que[10],h;
void update(const Point &p,int color)
{
	set<ID>::iterator it,tt;
	it=row[p.x].find(ID(p.y,color,0));
	tt=it;
	if(tt!=row[p.x].begin())
	{
		tt--;
		que[++h]=tt->c;
	}
	tt=it;
	tt++;
	if(tt!=row[p.x].end())
		que[++h]=tt->c;
	it=col[p.y].find(ID(p.x,color,0));
	tt=it;
	if(tt!=col[p.y].begin())
	{
		tt--;
		que[++h]=tt->c;
	}
	tt=it;
	tt++;
	if(tt!=col[p.y].end())
		que[++h]=tt->c;
}
bool vis[MAXN];
void solve2()
{
	for(int i=1;i<=N;i++)
		if(check(i))
		{
			Q.push(i);
			vis[i]=1;
		}
	while(!Q.empty())
	{
		int t=Q.front();
		Q.pop();
		h=0;
		update(P[t][0],t);
		update(P[t][1],t);
		sort(que+1,que+h+1);
		h=unique(que+1,que+h+1)-que-1;
		erase(t);
		for(int i=1;i<=h;i++)
			if(!vis[que[i]]&&check(que[i]))
			{
				Q.push(que[i]);
				vis[que[i]]=1;
			}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		printf("%d %d %c %c\n",output[i][0],output[i][1],output[i][2],output[i][3]);
}
int main()
{
	Read();
	Init();
	solve1();
	Init();
	solve2();
	return 0;
}
