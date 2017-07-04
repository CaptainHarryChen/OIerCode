#include<cstdio>
#include<cstring>
#include<algorithm>
using std::sort;
#define MAXN 1005
#define INF 0x7FFFFFFF
#define Point Vector
struct Vector
{
	int x,y;
	Vector(){}
	Vector(int a,int b):x(a),y(b){}
	Vector(Point a,Point b)
	{x=b.x-a.x;y=b.y-a.y;}
	int operator ^ (Vector t)const
	{return x*t.y-t.x*y;}
};
Point P[MAXN];
bool cmp(Point a,Point b)
{return a.x<b.x||(a.x==b.x&&a.y<b.y);}
int stack[MAXN],head;
bool used[MAXN];
bool judge()
{
	for(int i=1;i<head-2;i++)
		if((Vector(P[stack[i-1]],P[stack[i]])^Vector(P[stack[i-1]],P[stack[i+1]]))!=0&&
			(Vector(P[stack[i]],P[stack[i+1]])^Vector(P[stack[i]],P[stack[i+2]]))!=0)
			return 0;
	return 1;
}
int main()
{
	int test;
	scanf("%d",&test);
	while(test--)
	{
		memset(used,0,sizeof used);
		memset(P,0,sizeof P);
		memset(stack,0,sizeof stack);
		head=0;
		int n;
		Point mn=Point(INF,INF);
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&P[i].x,&P[i].y);
		if(n<6){puts("NO");continue;}
		sort(P+1,P+n+1,cmp);
		stack[head++]=1;
		stack[head++]=2;
		used[1]=used[2]=1;
		for(int i=3;i<=n;i++)
		{
			if(used[i])continue;
			while(head>=2&&((Vector(P[stack[head-2]],P[stack[head-1]])^
				Vector(P[stack[head-1]],P[i]))<0))
				{head--;used[stack[head]]=0;}
			stack[head++]=i;
			used[i]=1;
		}
		for(int i=n-1;i>0;i--)
		{
			if(used[i])continue;
			while(head>=2&&((Vector(P[stack[head-2]],P[stack[head-1]])^
				Vector(P[stack[head-1]],P[i]))<0))
				{head--;used[stack[head]]=0;}
			stack[head++]=i;
			used[i]=1;
		}
		stack[head++]=stack[0];
		stack[head++]=stack[1];
		if(judge())
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
