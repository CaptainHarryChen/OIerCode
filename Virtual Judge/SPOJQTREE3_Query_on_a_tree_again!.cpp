#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005;

struct Edge
{
	int v;
	Edge *nxt;
}E[MAXN*2],*V[MAXN],*cur=E;
void add_edge(int u,int v)
{
	cur->v=v;cur->nxt=V[u];
	V[u]=cur++;
	cur->v=u;cur->nxt=V[v];
	V[v]=cur++;
}

int fa[MAXN],siz[MAXN],son[MAXN],dep[MAXN];
int tid[MAXN],rnk[MAXN],top[MAXN],dcnt;
void dfs1(int u,int pa,int deep)
{
	fa[u]=pa;
	dep[u]=deep;
	son[u]=0;
	siz[u]=1;
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
	tid[u]=++dcnt;
	rnk[dcnt]=u;
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

int mn[MAXN*4],mxpos;
void PushUp(int u)
{mn[u]=min(mn[u*2],mn[u*2+1]);}
void Modify(int pos,int nval,int u=1,int L=1,int R=mxpos)
{
	if(R<pos||pos<L)return;
	if(L==pos&&pos==R)
	{
		mn[u]=nval;
		return;
	}
	int mid=(L+R)/2;
	Modify(pos,nval,u*2,L,mid);
	Modify(pos,nval,u*2+1,mid+1,R);
	PushUp(u);
}
int Query(int l,int r,int u=1,int L=1,int R=mxpos)
{
	if(R<l||r<L)return 0x7FFFFFFF;
	if(l<=L&&R<=r)
		return mn[u];
	int mid=(L+R)/2;
	return min(Query(l,r,u*2,L,mid),Query(l,r,u*2+1,mid+1,R));
}
int QueryPath(int a,int b)
{
	int res=0x7F7F7F7F;
	while(top[a]!=top[b])
	{
		if(dep[top[a]]>dep[top[b]])
			swap(a,b);
		res=min(res,Query(tid[top[b]],tid[b]));
		b=fa[top[b]];
	}
	if(dep[a]>dep[b])swap(a,b);
	res=min(res,Query(tid[a],tid[b]));
	return res==0x7F7F7F7F?0:res;
}

bool type[MAXN];
int main()
{
	int N,Q,op,a,b;
	scanf("%d%d",&N,&Q);
	for(int i=1;i<N;i++)
	{
		scanf("%d%d",&a,&b);
		add_edge(a,b);
	}
	memset(mn,0x7F,sizeof mn);
	mxpos=N;
	dfs1(1,0,1);
	dfs2(1,1);
	rnk[0]=-1;
	for(int i=1;i<=Q;i++)
	{
		scanf("%d%d",&op,&a);
		if(op==1)
			printf("%d\n",rnk[QueryPath(1,a)]);
		else
			if(type[a])
				Modify(tid[a],0x7F7F7F7F),type[a]=0;
			else
				Modify(tid[a],tid[a]),type[a]=1;
	}
	return 0;
}
