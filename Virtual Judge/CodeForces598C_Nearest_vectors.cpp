#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=100005;

struct Vector
{
	int id;
	long double x,y;
	Vector(){}
	Vector(long double _x,long double _y):x(_x),y(_y){}
	long double operator ^ (const Vector &t)const
	{return x*t.y-y*t.x;}
	long double operator * (const Vector &t)const
	{return x*t.x+y*t.y;}
	long double length()
	{return sqrt(x*x+y*y);}
};

bool cmp(const Vector &a,const Vector &b)
{
	return atan2(a.y,a.x)<atan2(b.y,b.x);
}

int n;
Vector V[MAXN];

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>V[i].x>>V[i].y;
		V[i].id=i;
	}
	sort(V+1,V+n+1,cmp);
	V[++n]=V[1];
	
	long double best=100000;
	int a=0,b=0;
	for(int i=1;i<n;i++)
	{
		long double tmp=atan2(V[i+1].y,V[i+1].x)-atan2(V[i].y,V[i].x);
		if(i==n-1)
			tmp+=2*acos(-1);
		if(tmp<best)
		{
			best=tmp;
			a=V[i].id;
			b=V[i+1].id;
		}
	}
	cout<<a<<' '<<b<<endl;
	
	return 0;
}
