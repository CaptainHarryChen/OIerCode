#include<cstdio>
#include<cmath>
#include<algorithm>
using std::sort;
#define MAXN 1005
#define INF 0x7FFFFFFF
#define Point Vector
typedef struct Vector
{
	int x,y;
	Vector(){}
	Vector(int a,int b):x(a),y(b){}
	Vector(Point a,Point b)
	{x=b.x-a.x;y=b.y-a.y;}
	int operator ^ (Vector t)const
	{return x*t.y-t.x*y;}
}Point;
Point P[MAXN];
bool cmp(Point a,Point b)
{return a.x<b.x||(a.x==b.x&&a.y<b.y);}
int stack[MAXN],head;
bool used[MAXN];
double dis(Point a,Point b)
{return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
int main()
{
	int n,l;
	Point mn=Point(INF,INF);
	scanf("%d%d",&n,&l);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&P[i].x,&P[i].y);
	sort(P+1,P+n+1,cmp);
	stack[head++]=1;
	stack[head++]=2;
	for(int i=3;i<=n;i++)
	{
		if(used[i])continue;
		while(head>=2&&((Vector(P[stack[head-2]],P[stack[head-1]])^
			Vector(P[stack[head-1]],P[i]))<=0))
			{head--;used[stack[head]]=0;}
		stack[head++]=i;
		used[i]=1;
	}
	for(int i=n-1;i>0;i--)
	{
		if(used[i])continue;
		while(head>=2&&((Vector(P[stack[head-2]],P[stack[head-1]])^
			Vector(P[stack[head-1]],P[i]))<=0))
			{head--;used[stack[head]]=0;}
		stack[head++]=i;
		used[i]=1;
	}
	double ans=0;
	for(int i=1;i<head;i++)
		ans+=dis(P[stack[i-1]],P[stack[i]]);
	ans+=dis(P[stack[0]],P[stack[head-1]]);
	ans+=2.0*l*3.141592653;
	printf("%d\n",(int)(ans+0.5));
	return 0;
}
