#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=20005;

struct Edge
{
	int v;
	Edge *nxt;
}E[MAXN*2],*V[MAXN],*cur;
void add_edge(int u,int v)
{
	cur->v=v,cur->nxt=V[u];
	V[u]=cur++;
	cur->v=u,cur->nxt=V[v];
	V[v]=cur++;
}

int val[MAXN];

int fa[MAXN],dep[MAXN],siz[MAXN],son[MAXN];
int tid[MAXN],rnk[MAXN],top[MAXN],dcnt;
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

int mx[MAXN*8],mn[MAXN*8],mxpos,n;
bool neg[MAXN*8];
void PushDown(int u)
{
	if(neg[u])
	{
		swap(mx[u],mn[u]);
		mx[u]=-mx[u];
		mn[u]=-mn[u];
		neg[u*2]^=neg[u];
		neg[u*2+1]^=neg[u];
		neg[u]=0;
	}
}
void PushUp(int u,int L,int R,int mid)
{
	PushDown(u);
	PushDown(u*2);
	PushDown(u*2+1);
	if(L==mid&&rnk[L]<=n)
	{
		mx[u]=mx[u*2+1],mn[u]=mn[u*2+1];
		return;
	}
	if(mid+1==R&&rnk[R]<=n)
	{
		mx[u]=mx[u*2],mn[u]=mn[u*2];
		return;
	}
	mx[u]=max(mx[u*2],mx[u*2+1]);
	mn[u]=min(mn[u*2],mn[u*2+1]);
}
void Build(int u=1,int L=1,int R=mxpos)
{
	PushDown(u);
	if(L==R)
	{
		mx[u]=val[rnk[L]];
		mn[u]=val[rnk[L]];
		return;
	}
	int mid=(L+R)/2;
	Build(u*2,L,mid);
	Build(u*2+1,mid+1,R);
	PushUp(u,L,R,mid);
}
void Modify(int pos,int nval,int u=1,int L=1,int R=mxpos)
{
	PushDown(u);
	if(L==pos&&R==pos)
	{
		mx[u]=nval;
		mn[u]=nval;
		return;
	}
	int mid=(L+R)/2;
	if(pos<=mid)
		Modify(pos,nval,u*2,L,mid);
	if(pos>mid)
		Modify(pos,nval,u*2+1,mid+1,R);
	PushUp(u,L,R,mid);
}
void Negate(int l,int r,int u=1,int L=1,int R=mxpos)
{
	PushDown(u);
	if(R<l||r<L)return;
	if(l<=L&&R<=r)
	{
		neg[u]^=1;
		PushDown(u);
		return;
	}
	int mid=(L+R)/2;
	Negate(l,r,u*2,L,mid);
	Negate(l,r,u*2+1,mid+1,R);
	PushUp(u,L,R,mid);
}
int Max(int l,int r,int u=1,int L=1,int R=mxpos)
{
	PushDown(u);
	if(R<l||r<L)return 0x80808080;
	if(L==R&&rnk[L]<=n)return 0x80808080;
	if(l<=L&&R<=r)
		return mx[u];
	int mid=(L+R)/2,res=0x80808080;
	res=Max(l,r,u*2,L,mid);
	res=max(res,Max(l,r,u*2+1,mid+1,R));
	PushUp(u,L,R,mid);
	return res;
}
void NegatePath(int a,int b)
{
	while(top[a]!=top[b])
	{
		if(dep[top[a]]>dep[top[b]])
			swap(a,b);
		Negate(tid[top[b]],tid[b]);
		b=fa[top[b]];
	}
	if(dep[a]>dep[b])
		swap(a,b);
	Negate(tid[a],tid[b]);
}
int QueryPath(int a,int b)
{
	int ans=0x80808080;
	while(top[a]!=top[b])
	{
		if(dep[top[a]]>dep[top[b]])
			swap(a,b);
		ans=max(ans,Max(tid[top[b]],tid[b]));
		b=fa[top[b]];
	}
	if(dep[a]>dep[b])
		swap(a,b);
	ans=max(ans,Max(tid[a],tid[b]));
	return ans;
}

void Init(int n)
{
	cur=E;
	memset(V,0,sizeof V);
	memset(val,0,sizeof val);
	memset(mx,0x80,sizeof mx);
	memset(mn,0x7F,sizeof mn);
	memset(neg,0,sizeof neg);
	mxpos=n+n-1;
	dcnt=0;
}
int main()
{
	int T;
	char op[10];
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		Init(n);
		for(int i=1,a,b,c;i<n;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			val[n+i]=c;
			add_edge(a,n+i);
			add_edge(n+i,b);
		}
		dfs1(1,0,1);
		dfs2(1,1);
		Build();
		while(true)
		{
			scanf("%s",op);
			if(op[0]=='D')
				break;
			int a,b;
			scanf("%d%d",&a,&b);
			if(op[0]=='C')
				Modify(tid[a+n],b);
			else if(op[0]=='N')
				NegatePath(a,b);
			else
				printf("%d\n",QueryPath(a,b));
		}
	}
	return 0;
}
