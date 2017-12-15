#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=50005;

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

int add[MAXN*4],mxpos;
void PushDown(int u)
{
	add[u*2]+=add[u];
	add[u*2+1]+=add[u];
	add[u]=0;
}
void Add(int l,int r,int aval,int u=1,int L=1,int R=mxpos)
{
	if(R<l||r<L)return;
	if(l<=L&&R<=r)
	{
		add[u]+=aval;
		return;
	}
	int mid=(L+R)/2;
	PushDown(u);
	Add(l,r,aval,u*2,L,mid);
	Add(l,r,aval,u*2+1,mid+1,R);
}
int Query(int pos,int u=1,int L=1,int R=mxpos)
{
	if(L==pos&&pos==R)
		return add[u];
	int mid=(L+R)/2;
	PushDown(u);
	if(pos<=mid)
		return Query(pos,u*2,L,mid);
	return Query(pos,u*2+1,mid+1,R);
}
void QAdd(int a,int b,int aval)
{
	while(top[a]!=top[b])
	{
		if(dep[top[a]]>dep[top[b]])
			swap(a,b);
		Add(tid[top[b]],tid[b],aval);
		b=fa[top[b]];
	}
	if(dep[a]>dep[b])swap(a,b);
	Add(tid[a],tid[b],aval);
}

int val[MAXN];
int main()
{
	int N,P,a,b,c;
	char op[10];
	while(scanf("%d%d%d",&N,&P,&P)!=EOF)
	{
		for(int i=1;i<=N;i++)
			scanf("%d",val+i);
		cur=E;
		memset(V,0,sizeof V);
		for(int i=1;i<N;i++)
		{
			scanf("%d%d",&a,&b);
			add_edge(a,b);
		}
		mxpos=N;
		dcnt=0;
		dfs1(1,0,1);
		dfs2(1,1);
		memset(add,0,sizeof add);
		for(int i=1;i<=P;i++)
		{
			scanf("%s",op);
			if(op[0]=='Q')
			{
				scanf("%d",&a);
				printf("%d\n",val[a]+Query(tid[a]));
			}
			else if(op[0]=='I')
			{
				scanf("%d%d%d",&a,&b,&c);
				QAdd(a,b,c);
			}
			else
			{
				scanf("%d%d%d",&a,&b,&c);
				QAdd(a,b,-c);
			}
		}
	}
	return 0;
}
