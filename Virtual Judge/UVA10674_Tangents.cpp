#include<cstdio>
#include<cmath>
#include<algorithm>
#define PI 3.141592653
using namespace std;
using std::abs;
using std::pair;
#define eps 0.00000001
typedef struct Vector
{
	double x,y;
	Vector(){x=y=0;}
	Vector(double a,double b):x(a),y(b){}
	Vector(Vector a,Vector b)
	{x=b.x-a.x;y=b.y-a.y;}
	void Read()
	{scanf("%lf%lf",&x,&y);}
	bool operator == (Vector t)const
	{return abs(x-t.x)<eps&&abs(y-t.y)<eps;}
	bool operator < (Vector t)const
	{return x<t.x||(abs(x-t.x)<eps&&y<t.y);}
	Vector operator + (Vector t)const
	{return Vector(x+t.x,y+t.y);}
	Vector operator - (Vector t)const
	{return Vector(x-t.x,y-t.y);}
	Vector operator * (double k)const
	{return Vector(x*k,y*k);}
	double operator * (Vector t)const
	{return x*t.x+y*t.y;}
	double length()
	{return sqrt((*this)*(*this));}
	Vector unit()
	{return (*this)*(1/(this->length()));}
}Point;
struct Circle
{
	Point O;
	double r;
	Circle(){}
	void Read()
	{O.Read();scanf("%lf",&r);}
	bool operator == (Circle t)const
	{return O==t.O&&abs(r-t.r)<eps;}
	Point getPoint(double a)
	{return Point(O.x+cos(a)*r,O.y+sin(a)*r);}
};
bool cmp(pair<Point,Point>a,pair<Point,Point>b)
{
	return a.first<b.first||(a.first==b.first&&a.second<b.second);
}
int CircleCircleTangents(Circle O1,Circle O2,pair<Point,Point>*P)
{
	if(O1==O2)return -1;
	int cnt=0;
	double o1o2=Vector(O1.O,O2.O).length();
	if(O1.r>O2.r)swap(O1,O2);
	if(o1o2+O1.r<O2.r)
		return 0;
	double base=atan2(O1.O.y-O2.O.y,O1.O.x-O2.O.x);
	if(abs(o1o2+O1.r-O2.r)<eps)
	{
		P[cnt].first=P[cnt].second=O1.getPoint(base);
		return 1;
	}
	double ang=acos((O2.r-O1.r)/o1o2);
	P[cnt].first=O1.getPoint(base-ang);
	P[cnt].second=O2.getPoint(base-ang);
	cnt++;
	P[cnt].first=O1.getPoint(base+ang);
	P[cnt].second=O2.getPoint(base+ang);
	cnt++;
	if(abs(O1.r+O2.r-o1o2)<eps)
	{
		P[cnt].first=O1.getPoint(PI+base);
		P[cnt].second=O2.getPoint(base);
		cnt++;
	}
	else if(o1o2>O1.r+O2.r)
	{
		ang=acos((O1.r+O2.r)/o1o2);
		P[cnt].first=O1.getPoint(PI+base-ang);
		P[cnt].second=O2.getPoint(base-ang);
		cnt++;
		P[cnt].first=O1.getPoint(PI+base+ang);
		P[cnt].second=O2.getPoint(base+ang);
		cnt++;
	}
	return cnt;
}
int main()
{
	Circle O1,O2;
	pair<Point,Point>P[4];
	while(1)
	{
		O1.Read();O2.Read();
		if(!O1.r&&!O2.r)break;
		int ans=CircleCircleTangents(O1,O2,P);
		printf("%d\n",ans);
		if(ans<=0)continue;
		if(O1.r>O2.r)
			for(int i=0;i<ans;i++)
				swap(P[i].first,P[i].second);
		sort(P,P+ans,cmp);
		for(int i=0;i<ans;i++)
			printf("%.5lf %.5lf %.5lf %.5lf %.5lf\n",
			P[i].first.x,P[i].first.y,
			P[i].second.x,P[i].second.y,
			Vector(P[i].first,P[i].second).length());
	}
	return 0;
}
