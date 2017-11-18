#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXLOG=20;

struct Node
{
	int cnt;
	Node *lch,*rch;
};

namespace SegTree
{
	int maxnum;
	Node nodes[MAXN*MAXLOG],*rt[MAXN],*cur,*null;
	void Init(int mx)
	{
		maxnum=mx;
		cur=nodes+1;
		null=nodes;
		null->cnt=0;
		null->lch=null->rch=null;
		rt[0]=null;
	}
	void Add(Node *&u,int pos,int L=1,int R=maxnum)
	{
		*cur=*u;
		u=cur++;
		u->cnt++;
		if(L==R)return;
		int mid=(L+R)/2;
		if(pos<=mid)
			Add(u->lch,pos,L,mid);
		else
			Add(u->rch,pos,mid+1,R);
	}
	int Query(Node *a,Node *b,Node *c,Node *d,int rk,int L=1,int R=maxnum)
	{
		if(L==R)return L;
		int midrk=a->lch->cnt+b->lch->cnt-c->lch->cnt-d->lch->cnt;
		int mid=(L+R)/2;
		if(rk<=midrk)
			return Query(a->lch,b->lch,c->lch,d->lch,rk,L,mid);
		return Query(a->rch,b->rch,c->rch,d->rch,rk-midrk,mid+1,R);
	}
}

namespace LCAtree
{
	int fa[MAXN][MAXLOG+3],lev[MAXN];
	vector<int>E[MAXN];
	void add_edge(int u,int v)
	{
		E[u].push_back(v);
		E[v].push_back(u);
	}
	void dfs(int u,int pa=0,int level=1)
	{
		fa[u][0]=pa;
		lev[u]=level;
		for(int i=0;i<(int)E[u].size();i++)
			if(E[u][i]!=pa)
				dfs(E[u][i],u,level+1);
	}
	void Init(int n)
	{
		dfs(1);
		for(int j=1;(1<<j)<=n;j++)
			for(int i=1;i<=n;i++)
				fa[i][j]=fa[fa[i][j-1]][j-1];
	}
	int LCA(int a,int b)
	{
		if(lev[a]>lev[b])
			swap(a,b);
		for(int i=MAXLOG;i>=0;i--)
			if(lev[b]-(1<<i)>=lev[a])
				b=fa[b][i];
		if(a==b)
			return a;
		for(int i=MAXLOG;i>=0;i--)
			if(lev[a]-(1<<i)>=1&&fa[a][i]!=fa[b][i])
				a=fa[a][i],b=fa[b][i];
		return fa[a][0];
	}
}

int val[MAXN],mp[MAXN];

void make_SegTree(int u,int pa=0)
{
	using namespace LCAtree;
	using namespace SegTree;
	rt[u]=rt[pa];
	Add(rt[u],val[u]);
	for(int i=0;i<(int)E[u].size();i++)
		if(E[u][i]!=pa)
			make_SegTree(E[u][i],u);
}
int solve(int u,int v,int k)
{
	using namespace SegTree;
	using namespace LCAtree;
	int lca=LCA(u,v);
	return mp[Query(rt[u],rt[v],rt[lca],rt[fa[lca][0]],k)];
}

int main()
{
	int N,M,a,b,u,v,k;
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",val+i);
		mp[i]=val[i];
	}
	sort(mp+1,mp+N+1);
	int num=unique(mp+1,mp+N+1)-mp-1;
	for(int i=1;i<=N;i++)
		val[i]=lower_bound(mp+1,mp+num+1,val[i])-mp;
	for(int i=1;i<N;i++)
	{
		scanf("%d%d",&a,&b);
		LCAtree::add_edge(a,b);
	}
	SegTree::Init(num);
	LCAtree::Init(N);
	make_SegTree(1);
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d%d",&u,&v,&k);
		printf("%d\n",solve(u,v,k));
	}
	return 0;
}
