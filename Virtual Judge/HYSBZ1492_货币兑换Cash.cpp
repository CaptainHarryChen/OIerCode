#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;

struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y)
	{x=_x;y=_y;}
	Point operator - (const Point &t)const
	{return Point(x-t.x,y-t.y);}
	double operator ^ (const Point &t)const
	{return x*t.y-y*t.x;}
	bool operator < (const Point &t)const
	{return x<t.x||(x==t.x&&y<t.y);}
};

int N,S;
double A[MAXN],B[MAXN],ra[MAXN];
double dp[MAXN];
Point lp[MAXN];
int stk[MAXN],top;

int Find(int i)
{
	if(top==1)return 1;
	int L=1,R=top;
	while(L<R)
	{
		int mid=(L+R)/2;
		if(((lp[stk[mid+1]]-lp[stk[mid]])^Point(-A[i],B[i]))>0)
			L=mid+1;
		else
			R=mid;
	}
	return L;
}


void CDQ(int L,int R)
{
	if(L>R)return;
	if(L==R)
	{
		dp[L]=max(dp[L],dp[L-1]);
		dp[L]=max(dp[L],1.0*S);
		return;
	}
	
	int mid=(L+R)/2;
	CDQ(L,mid);
	
	for(int i=L;i<=mid;i++)
		lp[i]=Point(dp[i]/(B[i]+ra[i]*A[i]),dp[i]*ra[i]/(B[i]+ra[i]*A[i]));
	sort(lp+L,lp+mid+1);
	
	top=0;
	for(int i=L;i<=mid;i++)
	{
		while(top>=2&&((lp[stk[top]]-lp[stk[top-1]])^(lp[i]-lp[stk[top]]))>=0)
			top--;
		stk[++top]=i;
	}
	for(int i=mid+1,j=1;i<=R;i++)
	{
		j=Find(i);
		j=stk[j];
		dp[i]=max(dp[i],lp[j].x*B[i]+lp[j].y*A[i]);
	}
	
	CDQ(mid+1,R);
}

int main()
{
	scanf("%d%d",&N,&S);
	for(int i=1;i<=N;i++)
		scanf("%lf%lf%lf",A+i,B+i,ra+i);
	
	CDQ(1,N);
	
	printf("%.3f\n",dp[N]);
	
	return 0;
}
