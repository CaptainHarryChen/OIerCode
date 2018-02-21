#include<cstdio>
#include<cmath>
#include<algorithm>
#include<set>
#define PI 3.141592653
#define MAXN 100005
using namespace std;
#define eps 1e-15
int dcmp(long double a,long double b)
{
    if(a-b>eps)return 1;
    else if(a-b>-eps)return 0;
    return -1;
}
typedef struct Vector
{
	long double x,y;
	Vector(){x=y=0.0;}
	Vector(long double a,long double b):x(a),y(b){}
	Vector(Vector a,Vector b)
	{x=b.x-a.x;y=b.y-a.y;}
	void Read()
	{
		int xx,yy;
		scanf("%d%d",&xx,&yy);
		x=xx;y=yy;
	}
	bool operator == (Vector t)const
	{return dcmp(x,t.x)==0&&dcmp(y,t.y)==0;}
	bool operator < (Vector t)const
	{return dcmp(x,t.x)==-1||(dcmp(x,t.x)==0&&dcmp(y,t.y)==-1);}
	Vector operator + (Vector t)const
	{return Vector(x+t.x,y+t.y);}
	Vector operator - (Vector t)const
	{return Vector(x-t.x,y-t.y);}
	Vector operator - ()
	{return Vector(-x,-y);}
	Vector operator * (long double k)const
	{return Vector(x*k,y*k);}
	long double operator * (Vector t)const
	{return x*t.x+y*t.y;}
	long double operator ^ (Vector t)const
	{return x*t.y-t.x*y;}
	long double length()
	{return sqrt((*this)*(*this));}
	Vector unit()
	{return (*this)*(1/(this->length()));}
}Point;
struct Line
{
    int id;
	long double aug;
	long double inter;
    Point a;
    Vector l;
    Line(){}
    Line(Point a,Point b):a(a){l=b-a;}
    void Read(int i=0)
    {a.Read();l.Read();id=i;l=l-a;}
}L[MAXN],l;
long double inters(Line x,Line y)
{
    Point p=x.a-y.a;
	long double S1=p^y.l;
    long double S2=y.l^(x.a+x.l-y.a);
    long double bl=S1/(S1+S2);
	return bl;
}
bool cmp(Line x,Line y)
{return dcmp(x.inter,y.inter)==-1;}
int sta[MAXN],top;
bool ans1[MAXN],ans2[MAXN];
multiset<long double>S1,S2;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        L[i].Read(i);
    l.Read();
    if(dcmp(Vector(0,1)^l.l,0)==1)
        l.l=Vector(0,0)-l.l;
    for(int i=1;i<=n;i++)
    {
        if(dcmp(l.l^L[i].l,0.0)==-1)
           L[i].l=-L[i].l;
        L[i].inter=inters(l,L[i]);
        long double cs=(l.l*L[i].l)
        /(l.l.length()*L[i].l.length());
        L[i].aug=acos(cs);
    }
    sort(L+1,L+n+1,cmp);
	for(int i=1;i<=n;i++)
		S1.insert(L[i].aug);
	for(int i=1;i<n;i++)
	{
		S2.insert(L[i].aug);
		S1.erase(S1.lower_bound(L[i].aug));
		if(dcmp((*S1.rbegin())-(*S2.begin()),0.0)==1)
			ans1[i]=1;
	}
	S1.clear();S2.clear();
	for(int i=1;i<=n;i++)
	{
		L[i].aug=3.141592653-L[i].aug;
		S1.insert(L[i].aug);
	}
	for(int i=1;i<n;i++)
	{
		S2.insert(L[i].aug);
		S1.erase(S1.lower_bound(L[i].aug));
		if(dcmp((*S1.rbegin())-(*S2.begin()),0.0)==1)
			ans2[i]=1;
	}
	printf("0");
	for(int i=1;i<=n;i++)
		printf("%d",ans1[i]&&ans2[i]);
	printf("\n");
    return 0;
}
