#include<cstdio>
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
}

int fa[MAXN],son[MAXN],siz[MAXN],dep[MAXN];
int tid[MAXN],rnk[MAXN],top[MAXN],dcnt;
void dfs1(int u,int pa,int deep)
{
	fa[u]=pa;dep[u]=deep;
	siz[u]=1;son[u]=0;
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
	tid[u]=++dcnt;rnk[dcnt]=u;
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

int cnt[MAXN*4],left[MAXN*4],right[MAXN*4];
int mxpos;
void PushDown(int u)
{
	if(cnt[u]==1)
	{
		cnt[u*2]=cnt[u*2+1]=1;
		left[u*2]=left[u*2+1]=right[u*2]=right[u*2+1]=left[u];
	}
}
void PushUp(int u)
{
	left[u]=left[u*2];
	right[u]=right[u*2+1];
	cnt[u]=cnt[u*2]+cnt[u*2+1]-(right[u*2]==left[u*2+1]);
}
void Build(const int col[],int u=1,int L=1,int R=mxpos)
{
	if(L==R)
	{
		cnt[u]=1;
		left[u]=right[u]=col[rnk[L]];
		return;
	}
	int mid=(L+R)/2;
	Build(col,u*2,L,mid);
	Build(col,u*2+1,mid+1,R);
	PushUp(u);
}
int Query(int l,int r,int &aleft,int &aright,int u=1,int L=1,int R=mxpos)
{
	if(l<=L&&R<=r)
	{
		aleft=left[u];
		aright=right[u];
		return cnt[u];
	}
	int mid=(L+R)/2,l1=-1,r1=-1,l2=-1,r2=-1,ct=0;
	PushDown(u);
	if(mid>=l&&r>=L)
		ct+=Query(l,r,l1,r1,u*2,L,mid);
	if(R>=l&&r>=mid+1)
		ct+=Query(l,r,l2,r2,u*2+1,mid+1,R);
	if(r1==l2&&r1!=-1)
		ct--;
	aleft=l1==-1?l2:l1;
	aright=r2==-1?r1:r2;
	return ct;
}
void Modify(int l,int r,int col,int u=1,int L=1,int R=mxpos)
{
	if(l<=L&&R<=r)
	{
		cnt[u]=1;
		left[u]=right[u]=col;
		return;
	}
	int mid=(L+R)/2;
	PushDown(u);
	if(mid>=l&&r>=L)
		Modify(l,r,col,u*2,L,mid);
	if(R>=l&&r>=mid+1)
		Modify(l,r,col,u*2+1,mid+1,R);
	PushUp(u);
}
void Pchange(int a,int b,int col)
{
	while(top[a]!=top[b])
	{
		if(dep[top[a]]>dep[top[b]])
			swap(a,b);
		Modify(tid[top[b]],tid[b],col);
		b=fa[top[b]];
	}
	if(dep[a]>dep[b])
		swap(a,b);
	Modify(tid[a],tid[b],col);
}
int Pquery(int a,int b)
{
	int res=0,la=-1,lb=-1,ta,tb,t;
	while(top[a]!=top[b])
	{
		if(dep[top[a]]>dep[top[b]])
		{
			swap(a,b);
			swap(la,lb);
		}
		res+=Query(tid[top[b]],tid[b],tb,t);
		if(t==lb)res--;
		lb=tb;
		b=fa[top[b]];
	}
	if(dep[a]>dep[b])
	{
		swap(a,b);
		swap(la,lb);
	}
	res+=Query(tid[a],tid[b],ta,tb);
	if(ta==la)res--;
	if(tb==lb)res--;
	return res;
}

int col[MAXN];
int main()
{
	int n,m,a,b,c;
	char op[5];
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",col+i);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add_edge(a,b);
		add_edge(b,a);
	}
	dfs1(1,0,1);
	dfs2(1,1);
	mxpos=n;
	Build(col);
	for(int i=1;i<=m;i++)
	{
		scanf("%s",op);
		if(op[0]=='Q')
		{
			scanf("%d%d",&a,&b);
			printf("%d\n",Pquery(a,b));
		}
		else
		{
			scanf("%d%d%d",&a,&b,&c);
			Pchange(a,b,c);
		}
	}
	return 0;
}
