#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=2005;

typedef struct Point Vector;
struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y){}
	Point operator - (const Point &t)const
	{return Point(x-t.x,y-t.y);}
	Point operator + (const Point &t)const
	{return Point(x+t.x,y+t.y);}
	long long operator ^ (const Vector &t)const
	{return 1LL*x*t.y-1LL*y*t.x;}
	bool operator < (const Point &t)const
	{return make_pair(x,y)<make_pair(t.x,t.y);}
};

struct Segment
{
	Vector v;
	int id1,id2;
	Segment(){}
	Segment(Vector _v,int _id1,int _id2)
	{v=_v;id1=_id1;id2=_id2;}
	bool operator < (const Segment &t)const
	{return (v^t.v)>0;}
};

int N,M;
long long S;
int pos[MAXN];
Point P[MAXN];
Segment seg[MAXN*MAXN];

long long TriangleArea(Point A,Point B,Point C)
{
	return abs((A^B)+(B^C)+(C^A));
}
void Finish(Point A,Point B,Point C)
{
	printf("Yes\n%d %d\n%d %d\n%d %d\n",A.x,A.y,B.x,B.y,C.x,C.y);
	exit(0);
}

int main()
{
	scanf("%d%I64d",&N,&S);
	S*=2LL;
	for(int i=1;i<=N;i++)
		scanf("%d%d",&P[i].x,&P[i].y);
	sort(P+1,P+N+1);
	for(int i=1;i<=N;i++)
		pos[i]=i;
	M=0;
	for(int i=1;i<=N;i++)
		for(int j=i+1;j<=N;j++)
			seg[++M]=Segment(P[j]-P[i],i,j);
	sort(seg+1,seg+M+1);
	for(int i=1;i<=M;i++)
	{
		int &a=pos[seg[i].id1];
		int &b=pos[seg[i].id2];
		int L=1,R=b-1;
		while(L<=R)
		{
			int mid=(L+R)/2;
			long long tmp=TriangleArea(P[a],P[b],P[mid]);
			if(tmp==S)
				Finish(P[a],P[b],P[mid]);
			if(tmp<S)
				R=mid-1;
			else
				L=mid+1;
		}
		L=a+1,R=N;
		while(L<=R)
		{
			int mid=(L+R)/2;
			long long tmp=TriangleArea(P[a],P[b],P[mid]);
			if(tmp==S)
				Finish(P[a],P[b],P[mid]);
			if(tmp<S)
				L=mid+1;
			else
				R=mid-1;
		}
		swap(P[a],P[b]);
		swap(a,b);
	}
	printf("No\n");
	
	return 0;
}
