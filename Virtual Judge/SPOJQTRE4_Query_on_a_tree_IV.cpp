#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=100005;
const int IMAX=0x7F7F7F7F,IMIN=0x80808080;

struct Heap
{
	priority_queue<int> heap,del;
	void push(int u)
	{heap.push(u);}
	void erase(int u)
	{del.push(u);}
	int size()
	{return heap.size()-del.size();}
	int top()
	{
		if(size()==0)return IMIN;
		while(!del.empty()&&heap.top()==del.top())
			heap.pop(),del.pop();
		return heap.top();
	}
	pair<int,int> top2()
	{
		pair<int,int> ret=make_pair(IMIN,IMIN);
		if(size()>=1)
		{
			ret.first=top();
			if(size()>=2)
			{
				erase(ret.first);
				ret.second=top();
				push(ret.first);
			}
		}
		return ret;
	}
};

struct Edge
{
	int v,d;
	Edge *nxt;
}E[MAXN*2],*V[MAXN],*ecnt=E;
void add_edge(int u,int v,int d)
{
	ecnt->v=v;ecnt->d=d;ecnt->nxt=V[u];
	V[u]=ecnt++;
	ecnt->v=u;ecnt->d=d;ecnt->nxt=V[v];
	V[v]=ecnt++;
}

int fa[MAXN],son[MAXN],siz[MAXN],dep[MAXN],dis[MAXN];
int top[MAXN],tid[MAXN],rnk[MAXN],rid[MAXN],dcnt;
void dfs1(int u,int pa,int deep,int dist)
{
	fa[u]=pa;dep[u]=deep;dis[u]=dist;
	siz[u]=1;son[u]=0;
	int best=0;
	for(Edge *p=V[u];p;p=p->nxt)
	{
		int v=p->v;
		if(v!=pa)
		{
			dfs1(v,u,deep+1,dist+p->d);
			siz[u]+=siz[v];
			if(best<siz[v])
				best=siz[v],son[u]=v;
		}
	}
}
void dfs2(int u,int tp)
{
	tid[u]=++dcnt;
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
	int mxl,mxr,mx;
	int dis;
	Node *lc,*rc;
};
Node *root[MAXN],nodes[MAXN*2],*ncnt=nodes;
bool col[MAXN];
Heap whi[MAXN],ans;
bool init;

void Update(Node *u,int id)
{
	int res=IMIN;
	if(!col[id])res=0;
	res=max(res,whi[id].top());
	u->mxl=u->mxr=res;
	if(!init)
		ans.erase(u->mx);
	pair<int,int> r=whi[id].top2();
	u->mx=IMIN;
	if(!col[id])
		u->mx=max(0,r.first);
	if(r.first!=IMIN&&r.second!=IMIN)
		u->mx=max(u->mx,r.first+r.second);
	ans.push(u->mx);
}
void PushUp(Node *u,int L,int mid,int R)
{
	int d=dis[rnk[mid+1]]-dis[rnk[mid]];
	if(u->lc->mxl==IMIN&&u->rc->mxl==IMIN)u->mxl=IMIN;
	else u->mxl=max(u->lc->mxl,u->rc->mxl+u->lc->dis+d);
	if(u->lc->mxr==IMIN&&u->rc->mxr==IMIN)u->mxr=IMIN;
	else u->mxr=max(u->lc->mxr+u->rc->dis+d,u->rc->mxr);
	if(!init)
		ans.erase(u->mx);
	u->mx=max(u->lc->mx,u->rc->mx);
	if(u->lc->mxr!=IMIN&&u->rc->mxl!=IMIN)
		u->mx=max(u->mx,u->lc->mxr+d+u->rc->mxl);
	ans.push(u->mx);
	u->dis=u->lc->dis+d+u->rc->dis;
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
				Build(root[top[v]],tid[top[v]],rid[top[v]]);
				if(root[top[v]]->mxl==IMIN)
					whi[t].push(IMIN);
				else
					whi[t].push(root[top[v]]->mxl+p->d);
			}
		}
		Update(u,t);
		return;
	}
	int mid=(L+R)/2;
	Build(u->lc,L,mid);
	Build(u->rc,mid+1,R);
	PushUp(u,L,mid,R);
}

void Modify(int pos,int od,int nw,Node *u,int L,int R)
{
	if(L==pos&&pos==R)
	{
		int t=rnk[pos];
		if(od!=IMAX)
		{
			whi[t].erase(od);
			whi[t].push(nw);
		}
		Update(u,t);
		return;
	}
	int mid=(L+R)/2;
	if(pos<=mid)
		Modify(pos,od,nw,u->lc,L,mid);
	else
		Modify(pos,od,nw,u->rc,mid+1,R);
	PushUp(u,L,mid,R);
}

void Modify(int x)
{
	int t,od=IMAX,nw=IMAX,d;
	while(x)
	{
		d=dis[top[x]]-dis[fa[top[x]]];
		t=root[top[x]]->mxl+d;
		if(root[top[x]]->mxl==IMIN)t=IMIN;
		Modify(tid[x],od,nw,root[top[x]],tid[top[x]],rid[top[x]]);
		od=t;
		nw=root[top[x]]->mxl+d;
		if(root[top[x]]->mxl==IMIN)
			nw=IMIN;
		x=fa[top[x]];
	}
}

int main()
{
	int N,Q,a,b,c,cnt;
	char op[5];
	scanf("%d",&N);
	cnt=N;
	for(int i=1;i<N;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
	}
	
	dfs1(1,0,1,0);
	dfs2(1,1);
	init=true;
	Build(root[1],tid[1],rid[1]);
	init=false;
	
	scanf("%d",&Q);
	for(int i=1;i<=Q;i++)
	{
		scanf("%s",op);
		if(op[0]=='C')
		{
			scanf("%d",&a);
			if(!col[a])
				cnt--,col[a]=1;
			else
				cnt++,col[a]=0;
			Modify(a);
		}
		else
		{
			if(cnt==0)puts("They have disappeared.");
			else printf("%d\n",ans.top());
		}
	}
	return 0;
}
