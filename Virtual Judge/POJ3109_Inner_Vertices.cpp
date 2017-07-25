#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;
typedef pair<int,int> Point;
class Tsum
{
	int sum[MAXN];
public:
	void add(int x,int val)
	{
		for(;x<MAXN;x+=(x&(-x)))
			sum[x]+=val;
	}
	int get(int x)
	{
		int ret=0;
		for(;x>0;x-=(x&(-x)))
			ret+=sum[x];
		return ret;
	}
};
int n;
Point P[MAXN];
int ed[MAXN];
bool added[MAXN];
Tsum Pcnt;
bool cmpy(const Point &a,const Point &b)
{return a.second<b.second||(a.second==b.second&&a.first<b.first);}
void input_init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&P[i].first,&P[i].second);
	int ix=0,iy=0;
	sort(P+1,P+n+1,cmpy);
	for(int i=1;i<=n;i++)
	{
		bool flag=0;
		if(P[i].second!=P[i+1].second)
			flag=1;
		P[i].second=iy;
		if(flag)
			iy++;
	}
	sort(P+1,P+n+1);
	for(int i=1;i<n;i++)
	{
		bool flag=0;
		if(P[i].first!=P[i+1].first)
			flag=1;
		P[i].first=ix;
		if(flag)
			ix++;
	}
	P[n].first=ix;
	for(int i=1;i<=n;i++)
		ed[P[i].second]=max(ed[P[i].second],P[i].first);
}
int scanningline()
{
	int ans=0;
	for(int i=1;i<n;i++)
	{
		int x=P[i].first,y=P[i].second;
		if(!added[y]&&x!=ed[y])
		{
			Pcnt.add(y,1);
			added[y]=1;
		}
		if(x==P[i+1].first)
		{
			if(P[i+1].second-y>1)
				ans+=(Pcnt.get(P[i+1].second-1)-Pcnt.get(y));
		}
		if(added[y]&&x==ed[y])
		{
			Pcnt.add(y,-1);
			added[y]=0;
		}
	}
	return ans+n;
}
int main()
{
	input_init();
	printf("%d\n",scanningline());
	return 0;
}
