#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 10 
#define MAX_HASH (long long)5000000
const int dd[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int ans[MAXN+1][MAXN+1][MAXN+1];
typedef struct XY
{
	int x,y;
	XY(){}
	XY(int a,int b):x(a),y(b){}
	bool operator<(XY t)const
	{return x<t.x||(x==t.x&&y<t.y);}
	bool operator==(XY t)const
	{return x==t.x&&y==t.y;}
}Block[11];
void translation(Block p)
{
	sort(p+1,p+p[0].x+1);
	int min_x=100,min_y=100;
	for(int i=1;i<=p[0].x;i++)
	{
		min_x=min(min_x,p[i].x);
		min_y=min(min_y,p[i].y);
	}
	for(int i=1;i<=p[0].x;i++)
		p[i].x-=min_x,p[i].y-=min_y;
}
void rotate(Block p)
{
	for(int i=1;i<=p[0].x;i++)
	{
		swap(p[i].x,p[i].y);
		p[i].y=-p[i].y;
	}
	translation(p);
}
void flip(Block p)
{
	for(int i=1;i<=p[0].x;i++)
		p[i].y=-p[i].y;
	translation(p);
}
struct HASH
{
	long long code;
	HASH *next;
	HASH(){code=-1;next=NULL;}
	HASH(long long c):code(c),next(NULL){}
}*head[MAX_HASH];
long long Code(const Block p)
{
	long long code=0;
	for(int i=2;i<=p[0].x;i++)
		code=code*100+(p[i].x-p[i-1].x)*10+(p[i].y-p[i-1].y);
	return code;
}
bool check_hash(long long code)
{
	for(HASH *h=head[code%MAX_HASH];h;h=h->next)
		if(h->code==code)
			return 1;
	return 0;
}
void insert_hash(long long code)
{
	if(!head[code%MAX_HASH])
		head[code%MAX_HASH]=new HASH(code);
	else
	{
		HASH *h=new HASH(code);
		h->next=head[code%MAX_HASH]->next;
		head[code%MAX_HASH]->next=h;
	}
}
bool mark(Block p)
{
	translation(p);
	long long code=Code(p);
	if(check_hash(code))
		return 0;
	for(int i=0;i<3;i++)
	{
		rotate(p);
		code=Code(p);
		if(check_hash(code))
			return 0;
	}
	flip(p);
	code=Code(p);
	if(check_hash(code))
		return 0;
	for(int i=0;i<3;i++)
	{
		rotate(p);
		code=Code(p);
		if(check_hash(code))
			return 0;
	}
	translation(p);
	code=Code(p);
	insert_hash(code);
	return 1;
}
struct BLOCKS
{
	int cnt;
	Block a[100000];
}blocks[MAXN+1];
bool find_point(XY t[],XY p)
{
	int x=lower_bound(t+1,t+t[0].x+1,p)-t;
	if(x==t[0].x+1)
		return 0;
	if(t[x]==p)
		return 1;
	return 0;
}
void getans()
{
	XY p;
	blocks[1].cnt=1;
	blocks[1].a[1][0].x=1;
	blocks[1].a[1][1]=XY(0,0);
	mark(blocks[1].a[1]);
	for(int i=2;i<=MAXN;i++)
		for(int j=1;j<=blocks[i-1].cnt;j++)
			for(int k=1;k<=blocks[i-1].a[j][0].x;k++)
				for(int d=0;d<4;d++)
				{
					p=blocks[i-1].a[j][k];
					p.x+=dd[d][0],p.y+=dd[d][1];
					if(!find_point(blocks[i-1].a[j],p))
					{
						Block pp;
						memcpy(pp,blocks[i-1].a[j],sizeof pp);
						pp[++pp[0].x]=p;
						if(mark(pp))
							memcpy(blocks[i].a[++blocks[i].cnt],pp,sizeof pp);
					}
				}
	for(int n=1;n<=MAXN;n++)
		for(int w=1;w<=MAXN;w++)
			for(int h=1;h<=MAXN;h++)
				for(int i=1;i<=blocks[n].cnt;i++)
				{
					int max_x=0,max_y=0;
					for(int j=1;j<=blocks[n].a[i][0].x;j++)
					{
						max_x=max(max_x,blocks[n].a[i][j].x);
						max_y=max(max_y,blocks[n].a[i][j].y);
					}
					if((min(max_x,max_y)<w&&max(max_x,max_y)<h)
						||(max(max_x,max_y)<w&&min(max_x,max_y)<h))
						ans[n][w][h]++;
				}
}
int main()
{
	getans();
	int n,w,h;
	while(~scanf("%d%d%d",&n,&w,&h))
		printf("%d\n",ans[n][w][h]);
	return 0;
}
