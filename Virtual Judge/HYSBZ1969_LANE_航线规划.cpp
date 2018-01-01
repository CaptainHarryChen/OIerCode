#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
const int MAXN=30005,MAXM=100005,MAXQ=40005;

typedef pair<int,int> iEdge;

struct Edge
{
	int v;
	Edge *nxt;
};
Edge E[MAXN*4],*V[MAXN*2],*ecnt=E;
void add_edge(int u,int v)
{
	ecnt->v=v;ecnt->nxt=V[u];
	V[u]=ecnt++;
	ecnt->v=u;ecnt->nxt=V[v];
	V[v]=ecnt++;
}

namespace HLD
{
	
int fa[MAXN*2],dep[MAXN*2],son[MAXN*2],siz[MAXN*2];
int top[MAXN*2],tid[MAXN*2],rnk[MAXN*2],dfsc;
void dfs1(int u,int pa,int deep)
{
	fa[u]=pa;
	dep[u]=deep;
	siz[u]=1;
	son[u]=0;
	int mx=0;
	for(Edge *p=V[u];p;p=p->nxt)
	{
		int v=p->v;
		if(v!=pa)
		{
			dfs1(v,u,deep+1);
			siz[u]+=siz[v];
			if(mx<siz[v])
				mx=siz[v],son[u]=v;
		}
	}
}
void dfs2(int u,int tp)
{
	tid[u]=++dfsc;
	rnk[dfsc]=u;
	top[u]=tp;
	if(son[u]==0)return;
	dfs2(son[u],tp);
	for(Edge *p=V[u];p;p=p->nxt)
	{
		int v=p->v;
		if(v!=fa[u]&&v!=son[u])
			dfs2(v,v);
	}
}


int sum[MAXN*8],n,mxpos;
bool flag[MAXN*8];

void PushDown(int u)
{
	if(flag[u])
	{
		sum[u]=0;
		flag[u*2]=true;
		flag[u*2+1]=true;
		flag[u]=false;
	}
}
void PushUp(int u)
{sum[u]=sum[u*2]+sum[u*2+1];}

void Build(int u=1,int L=1,int R=mxpos)
{
	if(L==R)
	{
		if(rnk[L]<=n)sum[u]=0;
		else sum[u]=1;
		return;
	}
	int mid=(L+R)/2;
	Build(u*2,L,mid);
	Build(u*2+1,mid+1,R);
	PushUp(u);
}

void Init(int N)
{
	dfsc=0;
	dfs1(1,0,1);
	dfs2(1,1);
	n=N;
	mxpos=n*2-1;
	Build();
}

void Modify(int l,int r,int u=1,int L=1,int R=mxpos)
{
	PushDown(u);
	if(R<l||r<L)
		return;
	if(l<=L&&R<=r)
	{
		sum[u]=0;
		if(L!=R)
			flag[u*2]=1,flag[u*2+1]=1;
		return;
	}
	int mid=(L+R)/2;
	Modify(l,r,u*2,L,mid);
	Modify(l,r,u*2+1,mid+1,R);
	PushUp(u);
}
int Query(int l,int r,int u=1,int L=1,int R=mxpos)
{
	PushDown(u);
	if(R<l||r<L)
		return 0;
	if(l<=L&&R<=r)
		return sum[u];
	int mid=(L+R)/2,res=0;
	res+=Query(l,r,u*2,L,mid);
	res+=Query(l,r,u*2+1,mid+1,R);
	return res;
}

void PathModify(int a,int b)
{
	while(top[a]!=top[b])
	{
		if(dep[top[a]]>dep[top[b]])
			swap(a,b);
		Modify(tid[top[b]],tid[b]);
		b=fa[top[b]];
	}
	if(dep[a]>dep[b])
		swap(a,b);
	Modify(tid[a],tid[b]);
}
int PathQuery(int a,int b)
{
	int res=0;
	while(top[a]!=top[b])
	{
		if(dep[top[a]]>dep[top[b]])
			swap(a,b);
		res+=Query(tid[top[b]],tid[b]);
		b=fa[top[b]];
	}
	if(dep[a]>dep[b])
		swap(a,b);
	res+=Query(tid[a],tid[b]);
	return res;
}

}

namespace UFset
{
	
int fa[MAXN];
int root(int x)
{
	if(fa[x]==0)
		return x;
	return fa[x]=root(fa[x]);
}

}

struct Order
{
	int type,a,b;
}order[MAXQ];
int Q;
iEdge org[MAXM],ins[MAXM],del[MAXQ];
int insc,delc;

int ans[MAXQ];

int main()
{
	int N,M;
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++)
		scanf("%d%d",&org[i].first,&org[i].second);
	Q=1;
	while(scanf("%d%d%d",&order[Q].type,&order[Q].a,&order[Q].b)==3)
	{
		if(order[Q].type==0)
			del[++delc]=iEdge(order[Q].a,order[Q].b);
		Q++;
	}
	Q--;
	
	sort(del+1,del+delc+1);
	
	for(int i=1;i<=M;i++)
	{
		if(*lower_bound(del+1,del+delc+1,org[i])==org[i])
			continue;
		org[i]=iEdge(org[i].second,org[i].first);
		if(*lower_bound(del+1,del+delc+1,org[i])==org[i])
			continue;
		
		int r1=UFset::root(org[i].first);
		int r2=UFset::root(org[i].second);
		if(r1==r2)
			ins[++insc]=org[i];
		else
		{
			add_edge(org[i].first,N+i);
			add_edge(N+i,org[i].second);
			UFset::fa[r1]=r2;
		}
	}
	
	HLD::Init(N);
	
	for(int i=1;i<=insc;i++)
		HLD::PathModify(ins[i].first,ins[i].second);
	
	for(int i=Q;i>0;i--)
	{
		if(order[i].type==1)
			ans[i]=HLD::PathQuery(order[i].a,order[i].b);
		else
		{
			ans[i]=-1;
			HLD::PathModify(order[i].a,order[i].b);
		}
	}
	
	for(int i=1;i<=Q;i++)
		if(ans[i]!=-1)
			printf("%d\n",ans[i]);
	return 0;
}
