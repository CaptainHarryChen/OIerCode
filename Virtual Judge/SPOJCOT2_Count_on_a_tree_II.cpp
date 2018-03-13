#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=40005,MAXM=100005,MAXLOG=20;

int N,M,blk;

struct Query
{
	int l,r,lca,id;
	bool operator < (const Query &t)const
	{return l/blk<t.l/blk||(l/blk==t.l/blk&&r<t.r);}
};

struct Edge
{
	int v;
	Edge *nxt;
};

int W[MAXN];
Edge E[MAXN*2],*adj[MAXN],*e_it=E;
void add_edge(int a,int b)
{
	e_it->v=b;e_it->nxt=adj[a];
	adj[a]=e_it++;
	e_it->v=a;e_it->nxt=adj[b];
	adj[b]=e_it++;
}

void Discretization()
{
	static int W2[MAXN];
	for(int i=1;i<=N;i++)
		W2[i]=W[i];
	sort(W2+1,W2+N+1);
	int n=unique(W2+1,W2+N+1)-W2-1;
	for(int i=1;i<=N;i++)
		W[i]=lower_bound(W2+1,W2+n+1,W[i])-W2;
}

pair<int,int> dfn[MAXN];
int id[MAXN*2];
int dfc;
int fa[MAXN][MAXLOG],lev[MAXN];

void dfs(int u,int dep,int f=0)
{
	lev[u]=dep;
	dfn[u].first=++dfc;
	fa[u][0]=f;
	for(Edge *p=adj[u];p;p=p->nxt)
		if(p->v!=f)
			dfs(p->v,dep+1,u);
	dfn[u].second=++dfc;
}

void Init()
{
	dfc=0;
	dfs(1,1);
	for(int j=1;(1<<j)<N;j++)
		for(int i=1;i<=N;i++)
			fa[i][j]=fa[fa[i][j-1]][j-1];
	for(int i=1;i<=N;i++)
		id[dfn[i].first]=id[dfn[i].second]=i;
}

int LCA(int a,int b)
{
	if(lev[a]>lev[b])
		swap(a,b);
	for(int i=MAXLOG-1;i>=0;i--)
		if(lev[b]-(1<<i)>=lev[a])
			b=fa[b][i];
	if(a==b)
		return a;
	for(int i=MAXLOG-1;i>=0;i--)
		if(lev[a]>(1<<i)&&fa[a][i]!=fa[b][i])
			a=fa[a][i],b=fa[b][i];
	return fa[a][0];
}

Query Q[MAXM];
int cnt[MAXN],ans[MAXM];
bool have[MAXN];
int l,r,res;

void op(int pos)
{
	have[id[pos]]^=1;
	if(have[id[pos]]==0)
		res-=((--cnt[W[id[pos]]])==0);
	else
		res+=((cnt[W[id[pos]]]++)==0);
}

void solve()
{
	l=r=res=1;
	have[id[1]]=true;
	cnt[W[id[1]]]=1;
	for(int i=1;i<=M;i++)
	{
		while(l>Q[i].l)
			l--,op(l);
		while(r<Q[i].r)
			r++,op(r);
		while(l<Q[i].l)
			op(l),l++;
		while(r>Q[i].r)
			op(r),r--;
		int temp=res;
		if(id[Q[i].l]!=Q[i].lca&&id[Q[i].r]!=Q[i].lca&&cnt[W[Q[i].lca]]==0)
			temp++;
		ans[Q[i].id]=temp;
	}
}

int main()
{
	scanf("%d%d",&N,&M);
	blk=sqrt(N*2);
	for(int i=1;i<=N;i++)
		scanf("%d",W+i);
	Discretization();
	
	for(int i=1,u,v;i<=N-1;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
	}
	Init();
	
	for(int i=1,u,v;i<=M;i++)
	{
		scanf("%d%d",&u,&v);
		Q[i].id=i;
		Q[i].lca=LCA(u,v);
		if(u==v)
			Q[i].l=Q[i].r=dfn[u].first;
		else if(Q[i].lca!=u&&Q[i].lca!=v)
		{
			Q[i].l=min(dfn[u].second,dfn[v].second);
			Q[i].r=max(dfn[u].first,dfn[v].first);
		}
		else
		{
			Q[i].l=min(dfn[u].first,dfn[v].first);
			Q[i].r=max(dfn[u].first,dfn[v].first);
		}
	}
	sort(Q+1,Q+M+1);
	
	solve();
	
	for(int i=1;i<=M;i++)
		printf("%d\n",ans[i]);
	
	return 0;
}
