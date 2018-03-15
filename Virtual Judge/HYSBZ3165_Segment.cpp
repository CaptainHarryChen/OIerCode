#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=40000,MOD=39989;
const double EPS=1e-6;

int fcmp(double a,double b)
{
	if(fabs(a-b)<EPS)
		return 0;
	if(a<b)
		return -1;
	return 1;
}

struct line
{
	int id;
	double k,b;
	line(){k=b=0.0;id=0;}
	line(double x1,double y1,double x2,double y2,int i)
	{
		if(fcmp(x1,x2)==0)
			k=0,b=y2;
		else
		{
			k=(y2-y1)/(x2-x1);
			b=y1-k*x1;
			id=i;
		}
	}
	double get_y(double x)
	{return x*k+b;}
	bool empty()
	{return fcmp(k,0)==0&&fcmp(b,0)==0;}
};
double intersection(line a,line b)
{return (b.b-a.b)/(a.k-b.k);}

namespace SegmentTree
{
	line best[MAXN*4];
	void Modify(line i,int L,int R,int id)
	{
		if(best[id].empty())
		{
			best[id]=i;
			return;
		}
		line a=best[id],b=i;
		if(fcmp(a.k,b.k)==0)
		{
			if(a.b>b.b)best[id]=a;
			else best[id]=b;
			return;
		}
		if(fcmp(a.k,b.k)==1)
			swap(a,b);
		double x=intersection(a,b);
		int mid=(L+R)/2;
		if(fcmp(x,L)==-1)
			best[id]=b;
		else if(fcmp(R,x)==-1)
			best[id]=a;
		else if(fcmp(x,mid)==-1)
			Modify(a,L,mid,id*2),best[id]=b;
		else
			Modify(b,mid+1,R,id*2+1),best[id]=a;
	}
	void Insert(int l,int r,line i,int L=1,int R=MAXN,int id=1)
	{
		if(l<=L&&R<=r)
		{
			Modify(i,L,R,id);
			return;
		}
		int mid=(L+R)/2;
		if(l<=mid)
			Insert(l,r,i,L,mid,id*2);
		if(mid<r)
			Insert(l,r,i,mid+1,R,id*2+1);
	}
	line Query(int pos,int L=1,int R=MAXN,int id=1)
	{
		line res=best[id],temp;
		if(L==R)
			return res;
		int mid=(L+R)/2;
		if(pos<=mid)
		{
			temp=Query(pos,L,mid,id*2);
			if(fcmp(res.get_y(pos),temp.get_y(pos))==-1||(fcmp(res.get_y(pos),temp.get_y(pos))==0&&temp.id<res.id))
				res=temp;
		}
		if(pos>mid)
		{
			temp=Query(pos,mid+1,R,id*2+1);
			if(fcmp(res.get_y(pos),temp.get_y(pos))==-1||(fcmp(res.get_y(pos),temp.get_y(pos))==0&&temp.id<res.id))
				res=temp;
		}
		return res;
	}
}

int main()
{
	int n,op,k,x1,y1,x2,y2,lastans=0,cnt=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&op);
		if(op==0)
		{
			scanf("%d",&k);
			k=(k+lastans-1)%MOD+1;
			lastans=SegmentTree::Query(k).id;
			printf("%d\n",lastans);
		}
		else
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			x1=(x1+lastans-1)%MOD+1;
			x2=(x2+lastans-1)%MOD+1;
			y1=(y1+lastans-1)%1000000000+1;
			y2=(y2+lastans-1)%1000000000+1;
			if(x1>x2)
				swap(x1,x2),swap(y1,y2);
			if(x1==x2&&y1>y2)
				swap(y1,y2);
			cnt++;
			SegmentTree::Insert(x1,x2,line(x1,y1,x2,y2,cnt));
		}
	}
	return 0;
}
