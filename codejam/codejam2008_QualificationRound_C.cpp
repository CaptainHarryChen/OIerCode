#include<cstdio>
#include<cmath>
using namespace std;
#define EPS 1e-100
inline int dcmp(double a,double b)
{
	if(a-b<-EPS)
		return -1;
	else if(a-b<=EPS)
		return 0;
	return 1;
}
inline int inround(double a,double b,double R)
{
	return dcmp(a*a+b*b,R*R)!=1;
}
inline double gg(double a,double b)
{
	return sqrt(a*a+b*b);
}
inline double ngg(double a,double b)
{
	return sqrt(a*a-b*b);
}
inline double Trapezoid(double a,double b,double h)
{
	return h*(a+b)/2;
}
inline double CircleSegment(double r,double th)
{
	return r*r*(th-sin(th))/2;
}
inline double Triangle(double a,double h)
{
	return a*h/2;
}
int main()
{
	int N;
	scanf("%d",&N);
	for(int Case=1;Case<=N;Case++)
	{
		double area1=0.0,area2;
		double f,R,t,r,g;
		scanf("%lf%lf%lf%lf%lf",&f,&R,&t,&r,&g);
		area2=R*R*M_PI/4;
		R-=t+f;
		r+=f;
		g-=2*f;
		if(dcmp(R,0.0)!=1||dcmp(g,0.0)!=1)
		{printf("Case #%d: %.6lf\n",Case,1.0);continue;}
		for(double x1=r;dcmp(x1,R)==-1;x1+=g+2*r)
			for(double y1=r;dcmp(y1,R)==-1;y1+=g+2*r)
			{
				if(!inround(x1,y1,R))continue;
				double x2=x1+g,y2=y1+g;
				if(inround(x2,y1,R)&&inround(x1,y2,R)&&inround(x2,y2,R))
				{
					area1+=g*g;
					continue;
				}
				if(!inround(x2,y1,R)&&inround(x1,y2,R)&&!inround(x2,y2,R))
				{
					area1+=Trapezoid(ngg(R,y1)-x1,ngg(R,y2)-x1,g);
					area1+=CircleSegment(R,asin(y2/R)-asin(y1/R));
					continue;
				}
				if(!inround(x2,y1,R)&&!inround(x1,y2,R)&&!inround(x2,y2,R))
				{
					area1+=Triangle(ngg(R,x1)-y1,ngg(R,y1)-x1);
					area1+=CircleSegment(R,acos(x1/R)-asin(y1/R));
					continue;
				}
				if(inround(x2,y1,R)&&inround(x1,y2,R)&&!inround(x2,y2,R))
				{
					area1+=g*g-Triangle(y2-(ngg(R,x2)),x2-(ngg(R,y2)));
					area1+=CircleSegment(R,asin(y2/R)-acos(x2/R));
					continue;
				}
				if(inround(x2,y1,R)&&!inround(x1,y2,R)&&!inround(x2,y2,R))
				{
					area1+=Trapezoid(ngg(R,x1)-y1,ngg(R,x2)-y1,g);
					area1+=CircleSegment(R,acos(x1/R)-acos(x2/R));
					continue;
				}
			}
		printf("Case #%d: %.6lf\n",Case,(area2-area1)/area2);
	}
	return 0;
}
