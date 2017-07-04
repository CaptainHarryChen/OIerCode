#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 500005
template<class T>
void Read(T &x)
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
			return;
		}
	}
}
int dd=0;
struct Point
{
	int pos[2];
	bool operator < (const Point &t)const
	{return pos[dd]<t.pos[dd];}
};
class kdTree
{
public:
	Point P[MAXN<<2];
	void ReadPoints(int n)
	{
		for(int i=1;i<=n;i++)
			Read(P[i].pos[0]),Read(P[i].pos[1]);
	}
	void Build(int L,int R,int id=1,int dep=0)
	{
		if(L>R)return;
		int mid=(L+R)>>1;
		dd=dep%2;
		nth_element(P+L,P+mid,P+R+1);
		Build(L,mid-1,id*2,dep+1);
		Build(mid+1,R,id*2+1,dep+1);
	}
	int QueryNearstDis(const Point &q,int L,int R,int dep=0)
	{
		if(L>R)return 0x7FFFFFFF;
		int mid=(L+R)>>1;
		int ans=abs(q.pos[0]-P[mid].pos[0])+abs(q.pos[1]-P[mid].pos[1]);
		dd=dep%2;
		int radius=abs(q.pos[dd]-P[mid].pos[dd]);
		if(q.pos[dd]<P[mid].pos[dd])
		{
			ans=min(ans,QueryNearstDis(q,L,mid-1,dep+1));
			if(radius<ans)ans=min(ans,QueryNearstDis(q,mid+1,R,dep+1));
		}
		else
		{
			ans=min(ans,QueryNearstDis(q,mid+1,R,dep+1));
			if(radius<ans)ans=min(ans,QueryNearstDis(q,L,mid-1,dep+1));
		}
		return ans;
	}
}kdT;
Point P[MAXN];
int main()
{
	int n,m;
	Read(n);Read(m);
	kdT.ReadPoints(n);
	kdT.Build(1,n);
	Point q;
	for(int i=1;i<=m;i++)
	{
		Read(q.pos[0]),Read(q.pos[1]);
		printf("%d\n",kdT.QueryNearstDis(q,1,n));
	}
	return 0;
}
