#include<cstdio>
#include<iostream>
using std::swap;
typedef struct Vector
{
	double x,y;
	Vector(){}
	Vector(double a,double b):x(a),y(b){}
	bool operator==(Vector t)const
	{return x==t.x&&y==t.y;}
	Vector operator+(Vector t)const
	{return Vector(x+t.x,y+t.y);}
}Point;
int main()
{
	Point a[2],b[2];
	Vector p,q,s;
	while(~scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&a[0].x,&a[0].y,&a[1].x,&a[1].y,&b[0].x,&b[0].y,&b[1].x,&b[1].y))
	{
		if(a[0]==b[1])swap(b[0],b[1]);
		if(a[1]==b[0])swap(a[0],a[1]);
		if(a[1]==b[1])swap(a[0],a[1]),swap(b[0],b[1]);
		p=Vector(a[1].x-a[0].x,a[1].y-a[0].y);
		q=Vector(b[1].x-b[0].x,b[1].y-b[0].y);
		s=p+q;
		printf("%.3lf %.3lf\n",a[0].x+s.x,a[0].y+s.y);
	}
	return 0;
}
