#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using std::priority_queue;
using std::pair;
using std::min;
using std::nth_element;
using std::make_pair;
#define MAXN 50005
#define MAXK 15
#define MAXD 5
template<class T>
bool Read(T &x)
{
	char c;
	bool f=0;
	while(c=getchar(),c!=EOF)
	{
		if(c=='-')
			f=1;
		else if(c>='0'&&c<='9')
		{
			x=c-'0';
			while(c=getchar(),c>='0'&&c<='9')
				x=x*10+c-'0';
			if(f)
				x=-x;
			return 1;
		}
	}
	return 0;
}
int dd=0;
struct Point
{
	int pos[MAXD];
	bool operator < (const Point &t)const
	{return pos[dd]<t.pos[dd];}
};
struct kdTree
{
	int D;
	Point P[MAXN];
	priority_queue< pair<int,Point> >ans;
	int getDis(Point a,Point b)
	{
		int ret=0;
		for(int i=0;i<D;i++)
			ret+=(a.pos[i]-b.pos[i])*(a.pos[i]-b.pos[i]);
		return ret;
	}
	void ReadPoints(int n,int d)
	{
		D=d;
		for(int i=1;i<=n;i++)
			for(int j=0;j<D;j++)
				Read(P[i].pos[j]);
	}
	void Build(int L,int R,int dep=0)
	{
		if(L>R)return;
		int mid=(L+R)>>1;
		dd=dep%D;
		nth_element(P+L,P+mid,P+R+1);
		Build(L,mid-1,dep+1);
		Build(mid+1,R,dep+1);
	}
	void QueryNearstDis(const Point &q,int L,int R,int K=1,int dep=0)
	{
		if(L>R)return;
		bool fg=0;
		int mid=(L+R)>>1;
		int dis=getDis(q,P[mid]);
		int dim=dep%D;
		int radius=(q.pos[dim]-P[mid].pos[dim])*(q.pos[dim]-P[mid].pos[dim]);
		if(q.pos[dim]<P[mid].pos[dim])
			QueryNearstDis(q,L,mid-1,K,dep+1);
		else
			QueryNearstDis(q,mid+1,R,K,dep+1);
		if((int)ans.size()<K)
		{ans.push(make_pair(dis,P[mid]));fg=1;}
		else
		{
			if(ans.top().first>dis)
			{ans.pop();ans.push(make_pair(dis,P[mid]));}
			if(radius<ans.top().first)
				fg=1;
		}
		if(fg&&q.pos[dim]<P[mid].pos[dim])
			QueryNearstDis(q,mid+1,R,K,dep+1);
		else if(fg)
			QueryNearstDis(q,L,mid-1,K,dep+1);
	}
	void PrintNearstPoints(int K)
	{
		Point pt[MAXK];
		for(int i=0;!ans.empty();i++)
			pt[i]=ans.top().second,ans.pop();
		for(int i=K-1;i>=0;i--)
		{
			for(int j=0;j<D-1;j++)
				printf("%d ",pt[i].pos[j]);
			printf("%d\n",pt[i].pos[D-1]);
		}
	}
}kdT;
Point P[MAXN];
int main()
{
	int n,m,d;
	while(Read(n)&&Read(d))
	{
		kdT.ReadPoints(n,d);
		kdT.Build(1,n);
		Point q;
		Read(m);
		for(int i=1,k;i<=m;i++)
		{
			for(int j=0;j<d;j++)
				Read(q.pos[j]);
			Read(k);
			kdT.QueryNearstDis(q,1,n,k);
			printf("the closest %d points are:\n",k);
			kdT.PrintNearstPoints(k);
		}
	}
	return 0;
}
