#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=30005;

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

int mx[MAXN*4],mxpos;
long long sum[MAXN*4];
void PushUp(int u)
{
	mx[u]=max(mx[u*2],mx[u*2+1]);
	sum[u]=sum[u*2]+sum[u*2+1];
}
void Modify(int pos,int nval,int u=1,int L=1,int R=mxpos)
{
	if(R<pos||pos<L)return;
	if(L==pos&&pos==R)
	{
		mx[u]=nval;
		sum[u]=nval;
		return;
	}
	int mid=(L+R)/2;
	Modify(pos,nval,u*2,L,mid);
	Modify(pos,nval,u*2+1,mid+1,R);
	PushUp(u);
}
int Max(int l,int r,int u=1,int L=1,int R=mxpos)
{
	if(R<l||r<L)return 0x80808080;
	if(l<=L&&R<=r)
		return mx[u];
	int mid=(L+R)/2;
	return max(Max(l,r,u*2,L,mid),Max(l,r,u*2+1,mid+1,R));
}
long long Sum(int l,int r,int u=1,int L=1,int R=mxpos)
{
	if(R<l||r<L)return 0;
	if(l<=L&&R<=r)
		return sum[u];
	int mid=(L+R)/2;
	return Sum(l,r,u*2,L,mid)+Sum(l,r,u*2+1,mid+1,R);
}
int QMax(int a,int b)
{
	int res=0x80808080;
	while(top[a]!=top[b])
	{
		if(dep[top[a]]>dep[top[b]])
			swap(a,b);
		res=max(res,Max(tid[top[b]],tid[b]));
		b=fa[top[b]];
	}
	if(dep[a]>dep[b])swap(a,b);
	res=max(res,Max(tid[a],tid[b]));
	return res;
}
long long QSum(int a,int b)
{
	long long res=0;
	while(top[a]!=top[b])
	{
		if(dep[top[a]]>dep[top[b]])
			swap(a,b);
		res+=Sum(tid[top[b]],tid[b]);
		b=fa[top[b]];
	}
	if(dep[a]>dep[b])swap(a,b);
	res+=Sum(tid[a],tid[b]);
	return res;
}

int main()
{
	int N,Q,a,b;
	char op[10];
	scanf("%d",&N);
	for(int i=1;i<N;i++)
	{
		scanf("%d%d",&a,&b);
		add_edge(a,b);
	}
	mxpos=N;
	dfs1(1,0,1);
	dfs2(1,1);
	memset(mx,0x80,sizeof mx);
	for(int i=1,x;i<=N;i++)
	{
		scanf("%d",&x);
		Modify(tid[i],x);
	}
	scanf("%d",&Q);
	for(int i=1;i<=Q;i++)
	{
		scanf("%s%d%d",op,&a,&b);
		if(op[1]=='M')
			printf("%d\n",QMax(a,b));
		else if(op[1]=='S')
			printf("%lld\n",QSum(a,b));
		else
			Modify(tid[a],b);
	}
	return 0;
}
