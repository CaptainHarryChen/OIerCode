#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const long long MAXN=100005;

namespace DSU
{
	long long fa[MAXN];
	void Clear()
	{memset(fa,-1,sizeof fa);}
	long long Root(long long x)
	{return fa[x]==-1?x:(fa[x]=Root(fa[x]));}
	void Union(long long x,long long y)
	{
		long long r1=Root(x),r2=Root(y);
		if(r1!=r2)
			fa[r1]=r2;
	}
}

struct Vertice
{
	long long val,id;
	Vertice(){val=0x3F3F3F3F3F3F3F3FLL;}
	Vertice(long long v,long long i){val=v;id=i;}
	bool operator < (const Vertice &t)const
	{return val<t.val;}
};

Vertice V[MAXN],tr[MAXN];
bool used[MAXN];
bool mk[MAXN];

int main()
{
	long long n,m;
	scanf("%lld%lld",&n,&m);
	for(long long i=0,a;i<n;i++)
	{
		scanf("%lld",&a);
		V[i]=Vertice(a,i);
	}
	DSU::Clear();
	for(long long i=0,u,v;i<m;i++)
	{
		scanf("%lld%lld",&u,&v);
		DSU::Union(u,v);
	}
	int cc=0;
	for(int i=0;i<n;i++)
		if(!mk[DSU::Root(i)])
		{
			mk[DSU::Root(i)]=true;
			cc++;
		}
	if(cc==1)
	{
		puts("0");
		return 0;
	}
	if(2*cc-2>n)
	{
		puts("Impossible");
		return 0;
	}
	for(long long i=0;i<n;i++)
	{
		int r=DSU::Root(i);
		tr[r]=min(tr[r],V[i]);
	}
	long long ans=0,cnt=2*cc-2;
	for(long long i=0;i<n&&cnt;i++)
	{
		int r=DSU::Root(i);
		if(!used[tr[r].id])
		{
			ans+=tr[r].val;
			used[tr[r].id]=true;
			cnt--;
		}
	}
	sort(V,V+n);
	for(long long i=0;i<n&&cnt;i++)
		if(!used[V[i].id])
		{
			ans+=V[i].val;
			cnt--;
		}
	
	printf("%lld\n",ans);
	return 0;
}
