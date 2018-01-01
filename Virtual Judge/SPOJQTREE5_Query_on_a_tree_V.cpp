#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=100005;
const int IMAX=0x7F7F7F7F,IMIN=0x80808080;

struct Heap
{
	priority_queue< int,vector<int>,greater<int> >heap,del;
	void push(int u)
	{heap.push(u);}
	void erase(int u)
	{del.push(u);}
	int top()
	{
		while(!del.empty()&&heap.top()==del.top())
			heap.pop(),del.pop();
		return heap.top();
	}
	int size()
	{return heap.size()-del.size();}
};

struct Edge
{
	int v;
	Edge *nxt;
}E[MAXN*2],*V[MAXN],*ecnt=E;
void add_edge(int u,int v)
{
	ecnt->v=v;ecnt->nxt=V[u];
	V[u]=ecnt++;
	ecnt->v=u;ecnt->nxt=V[v];
	V[v]=ecnt++;
}

int fa[MAXN],son[MAXN],siz[MAXN],dep[MAXN];
int top[MAXN],tid[MAXN],rnk[MAXN],dcnt;
int lid[MAXN],rid[MAXN];
void dfs1(int u,int pa,int deep)
{
	fa[u]=pa;dep[u]=deep;
	siz[u]=1;son[u]=0;
	int best=0;
	for(Edge *p=V[u];p;p=p->nxt)
	{
		int v=p->v;
		if(v!=pa)
		{
			dfs1(v,u,deep+1);
			siz[u]+=siz[v];
			if(best<siz[v])
				best=siz[v],son[u]=v;
		}
	}
}
void dfs2(int u,int tp)
{
	tid[u]=++dcnt;
	if(u==tp)lid[u]=dcnt;
	rnk[dcnt]=u;
	top[u]=tp;
	rid[tp]=dcnt;
	if(son[u]==0)return;
	dfs2(son[u],tp);
	for(Edge *p=V[u];p;p=p->nxt)
	{
		int v=p->v;
		if(v!=fa[u]&&v!=son[u])
			dfs2(v,v);
	}
}

struct Node
{
	int mnl,mnr;
	Node *lc,*rc;
};
Node *root[MAXN],nodes[MAXN*2],*ncnt=nodes;
bool col[MAXN];
Heap oth[MAXN];

void Update(Node *u,int id)
{
	int res=IMAX;
	if(col[id])
		res=0;
	if(oth[id].size())
		res=min(res,oth[id].top()+1);
	u->mnl=u->mnr=res;
}
void PushUp(Node *u,int L,int R)
{
	int mid=(L+R)/2;
	u->mnl=min(u->lc->mnl,u->rc->mnl+mid+1-L);
	u->mnr=min(u->lc->mnr+R-mid,u->rc->mnr);
}
void Build(Node *&u,int L,int R)
{
	if(u==NULL)u=ncnt++;
	if(L==R)
	{
		int t=rnk[L];
		for(Edge *p=V[t];p;p=p->nxt)
		{
			int v=p->v;
			if(v!=fa[t]&&top[v]!=top[t])
			{
				Build(root[top[v]],tid[v],rid[top[v]]);
				oth[t].push(root[top[v]]->mnl+1);
			}
		}
		Update(u,t);
		return;
	}
	int mid=(L+R)/2;
	Build(u->lc,L,mid);
	Build(u->rc,mid+1,R);
	PushUp(u,L,R);
}
void Modify(int pos,int od,int nw,Node *u,int L,int R)
{
	if(pos==L&&R==pos)
	{
		if(od!=-1)
		{
			int t=rnk[pos];
			oth[t].erase(od);
			oth[t].push(nw);
		}
		Update(u,rnk[pos]);
		return;
	}
	int mid=(L+R)/2;
	if(pos<=mid)
		Modify(pos,od,nw,u->lc,L,mid);
	else
		Modify(pos,od,nw,u->rc,mid+1,R);
	PushUp(u,L,R);
}
int Query(int l,int r,bool f,Node *u,int L,int R)
{
	if(l<=L&&R<=r)
		return f?u->mnr:u->mnl;
	int mid=(L+R)/2,r1=IMAX,r2=IMAX;
	if(l<=mid)
	{
		r1=Query(l,r,f,u->lc,L,mid);
		if(f&&r>mid)r1+=r-mid;
	}
	if(r>mid)
	{
		r2=Query(l,r,f,u->rc,mid+1,R);
		if(!f&&l<=mid)r2+=mid+1-l;
	}
	return min(r1,r2);
}
void Modify(int u)
{
	int od=-1,nw=-1,t;
	while(u)
	{
		t=root[top[u]]->mnl;
		Modify(tid[u],od,nw,root[top[u]],lid[top[u]],rid[top[u]]);
		od=t;
		nw=root[top[u]]->mnl;
		u=fa[top[u]];
	}
}
int Query(int u)
{
	int res=IMAX,dis=0,last=u;
	while(u)
	{
		res=min(res,Query(tid[u],rid[top[u]],0,root[top[u]],lid[top[u]],rid[top[u]])+dis);
		res=min(res,Query(lid[top[u]],tid[u],1,root[top[u]],lid[top[u]],rid[top[u]])+dis);
		last=u;
		u=fa[top[u]];
		dis+=dep[last]-dep[u];
	}
	return res;
}

int main()
{
	int N,Q,op,a,b,cnt=0;
	scanf("%d",&N);
	for(int i=1;i<N;i++)
	{
		scanf("%d%d",&a,&b);
		add_edge(a,b);
	}
	
	dfs1(1,0,1);
	dfs2(1,1);
	Build(root[1],lid[1],rid[1]);
	
	scanf("%d",&Q);
	for(int i=1;i<=Q;i++)
	{
		scanf("%d%d",&op,&a);
		if(op==0)
		{
			if(col[a])
				cnt--,col[a]=0;
			else
				cnt++,col[a]=1;
			Modify(a);
		}
		else
		{
			if(cnt==0)puts("-1");
			else printf("%d\n",Query(a));
		}
	}
	return 0;
}
