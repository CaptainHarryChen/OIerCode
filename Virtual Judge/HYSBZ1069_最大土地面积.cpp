#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=2005;
const double EPS=1e-5;

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
	Vector(int x,int y):x(x),y(y){}
	void Read()
	{scanf("%lf%lf",&x,&y);}
	Vector operator - (const Vector &t)const
	{return Vector(x-t.x,y-t.y);}
	double operator ^ (const Vector &t)const
	{return x*t.y-y*t.x;}
	double length()
	{return sqrt(x*x+y*y);}
};
bool cmp(const Point &a,const Point &b)
{return	fcmp(a.x,b.x)==-1||(fcmp(a.x,b.x)==0&&fcmp(a.y,b.y)==-1);}

int ConvecHull(Point P[],int res[],int N)
{
	sort(P+1,P+N+1,cmp);
	int top=0;
	for(int i=1;i<=N;i++)
	{
		while(top>=2)
		{
			Point A=P[res[top-1]],B=P[res[top]],C=P[i];
			if(fcmp((B-A)^(C-B),0)!=1)
				top--;
			else break;
		}
		res[++top]=i;
	}
	int temp=top;
	for(int i=N-1;i>0;i--)
	{
		while(top-temp>=1)
		{
			Point A=P[res[top-1]],B=P[res[top]],C=P[i];
			if(fcmp((B-A)^(C-B),0)!=1)
				top--;
			else break;
		}
		res[++top]=i;
	}
	top--;
	return top;
}
double RotatingCaliper(const Point P[],const int id[],int n)
{
	double res=0,S;
	for(int i=1;i<=n;i++)
	{
		int p1=i%n+1,p2=i;
		for(int j=i+1;j<=n;j++)
		{
			Point A=P[id[i]],B=P[id[j]],C=P[id[p1]],D=P[id[p2]];
			for(;fcmp((B-A)^(C-A),(B-A)^(P[id[p1+1]]-A))==-1;C=P[id[p1]])
				p1=p1%n+1;
			for(;fcmp((D-A)^(B-A),(P[id[p2+1]]-A)^(B-A))==-1;D=P[id[p2]])
				p2=p2%n+1;
			S=((B-A)^(C-A))+((D-A)^(B-A));
			if(fcmp(res,S)==-1)
				res=S;
		}
	}
	return res/2;
}

Point P[MAXN];
int CH[MAXN];

int main()
{
	int n,m;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		P[i].Read();
	m=ConvecHull(P,CH,n);
	printf("%.3lf\n",RotatingCaliper(P,CH,m));
	
	return 0;
}
