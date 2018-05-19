#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=505;
const double EPS=1e-10;

int fcmp(double a,double b)
{
	if(fabs(a-b)<=EPS)
		return 0;
	if(a<b)
		return -1;
	return 1;
}

typedef struct Vector Point;
struct Vector
{
	double x,y;
	Vector(){}
	Vector(double x,double y):x(x),y(y){}
	void Read()
	{scanf("%lf%lf",&x,&y);}
	Vector operator - (const Vector &t)const
	{return Vector(x-t.x,y-t.y);}
	Vector operator + (const Vector &t)const
	{return Vector(x+t.x,y+t.y);}
	Vector operator * (double k)const
	{return Vector(x*k,y*k);}
	double operator ^ (const Vector &t)const
	{return x*t.y-y*t.x;}
	double length()
	{return sqrt(x*x+y*y);}
};
struct Line
{
	Point p;
	Vector v;
	double ang;
	Line(){}
	Line(const Point &a,const Point &b)
	{p=a;v=b-a;ang=atan2(v.y,v.x);}
	bool operator < (const Line &t)const
	{return fcmp(ang,t.ang)==-1;}
	bool OnLeft(const Point &t)const
	{return fcmp(v^(t-p),0)==1;}
};
Point Intersection(const Line &a,const Line &b)
{
	return a.p+a.v*(((b.p-a.p)^(b.v))/(a.v^b.v));
}

int Q[MAXN],head,tail;
int HalfplaneIntersection(Line L[],Point res[],int n)
{
	sort(L+1,L+n+1);
	head=tail=1;
	Q[1]=1;
	for(int i=2;i<=n;i++)
	{
		while(head<tail&&!L[i].OnLeft(res[tail-1]))
			tail--;
		while(head<tail&&!L[i].OnLeft(res[head]))
			head++;
		if(fcmp(L[i].v^L[Q[tail]].v,0)==0)
		{
			if(L[i].OnLeft(L[Q[tail]].p))
				continue;
			tail--;
		}
		Q[++tail]=i;
		if(head<tail)
			res[tail-1]=Intersection(L[Q[tail]],L[Q[tail-1]]);
	}
	while(head<tail&&!L[Q[head]].OnLeft(res[tail-1]))
		tail--;
	if(tail-head<=1)
		return 0;
	res[tail]=Intersection(L[Q[head]],L[Q[tail]]);
	for(int i=1;i<=tail-head+1;i++)
		res[i]=res[head+i-1];
	return tail-head+1;
}

Line L[MAXN];
Point poly[MAXN];

int main()
{
	int num=0;
	int n,m;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&m);
		Point st,last,p;
		st.Read();
		last=st;
		for(int j=2;j<=m;j++)
		{
			p.Read();
			L[++num]=Line(last,p);
			last=p;
		}
		L[++num]=Line(p,st);
	}
	m=HalfplaneIntersection(L,poly,num);
	double ans=0;
	if(m>2)
	{
		for(int i=1;i<m;i++)
			ans+=(poly[i]^poly[i+1])/2;
		ans+=(poly[m]^poly[1])/2;
	}
	printf("%.3lf\n",ans);
	
	return 0;
}
