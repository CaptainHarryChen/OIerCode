#include<algorithm>
#include<cstdio>
#include<cmath>
using std::sort;
using std::unique;
#define MAXN 400010
int dcmp(double a,double b)
{
	if(a-b>0.000000001)return 1;
	else if(a-b>=-0.000000001)return 0;
	else return -1;
}
typedef struct Vector
{
	double x,y;
	Vector(){}
	Vector(double x,double y):x(x),y(y){}
	Vector(Vector a,Vector b)
	{x=b.x-a.x;y=b.y-a.y;}
	void Read()
	{scanf("%lf%lf",&x,&y);}
	bool operator < (Vector t)const
	{return dcmp(x,t.x)==-1||(dcmp(x,t.x)==0&&dcmp(y,t.y)==-1);}
	bool operator == (Vector t)const
	{return dcmp(x,t.x)==0&&dcmp(y,t.y)==0;}
	Vector operator + (Vector t)
	{return Vector(x+t.x,y+t.y);}
	double operator ^ (Vector t)
	{return x*t.y-y*t.x;}
	Vector Rotate(double a)
	{return Vector(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));}
	double Length()
	{return sqrt(x*x+y*y);}
}Point;
Point P[MAXN];
int TuBao[MAXN];
bool used[MAXN];
int make_TuBao(Point P[],int s,int t,int stack[])
{
	int top=0;
	sort(P+s,P+t+s+1);
	t=unique(P+s,P+t+s+1)-P-1;
	stack[top++]=s;
	stack[top++]=s+1;
	for(int i=s+2;i<=t;i++)
	{
		if(used[i])continue;
		while(top>=2&&dcmp((Vector(P[stack[top-2]],P[stack[top-1]])
			^Vector(P[stack[top-1]],P[i])),0.0)<=0)
			{top--;used[stack[top]]=0;}
		stack[top++]=i;
		used[i]=1;
	}
	for(int i=t-1;i>=s;i--)
	{
		if(used[i])continue;
		while(top>=2&&dcmp((Vector(P[stack[top-2]],P[stack[top-1]])
			^Vector(P[stack[top-1]],P[i])),0)<=0)
			{top--;used[stack[top]]=0;}
		stack[top++]=i;
		used[i]=1;
	}
	return top;
}
int main()
{
	int n;
	scanf("%d",&n);
	Point o;
	Vector t;
	double a,b,r,th;
	scanf("%lf%lf%lf",&a,&b,&r);
	for(int i=0;i<n;i++)
	{
		o.Read();scanf("%lf",&th);
		t=Vector(b/2-r,a/2-r);
		t=t.Rotate(th);
		P[i*4]=o+t;
		t=Vector(b/2-r,-a/2+r);
		t=t.Rotate(th);
		P[i*4+1]=o+t;
		t=Vector(-b/2+r,a/2-r);
		t=t.Rotate(th);
		P[i*4+2]=o+t;
		t=Vector(-b/2+r,-a/2+r);
		t=t.Rotate(th);
		P[i*4+3]=o+t;
	}
	int cnt=make_TuBao(P,0,n*4-1,TuBao);
	double len=0;
	for(int i=1;i<cnt;i++)
		len+=Vector(P[TuBao[i-1]],P[TuBao[i]]).Length();
	len+=2*r*3.141592653;
	printf("%.2lf\n",len);
	return 0;
}
