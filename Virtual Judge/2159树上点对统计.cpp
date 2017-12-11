#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAXN=10005;

namespace Treap
{
	struct Node
	{
		int key,fix,siz;
		Node *lch,*rch;
		Node(){}
		Node(int val,Node *nul)
		{key=val;fix=rand();siz=1;lch=rch=nul;}
		void Update()
		{siz=1+lch->siz+rch->siz;}
	};
	Node nodes[MAXN],*null,*cur,*root;
	void Clear()
	{
		null=nodes;
		null->key=null->fix=null->siz=0;
		null->lch=null->rch=null;
		cur=nodes+1;
		root=null;
	}
	Node *NewNode(int val)
	{
		*cur=Node(val,null);
		return cur++;
	}
	Node *Merge(Node *A,Node *B)
	{
		if(A==null)return B;
		if(B==null)return A;
		Node *t;
		if(A->fix<B->fix)
			A->rch=Merge(A->rch,B),t=A;
		else
			B->lch=Merge(A,B->lch),t=B;
		t->Update();
		return t;
	}
	void Split(int val,Node *u,Node *&ansL,Node *&ansR)
	{
		if(u==null)
		{
			ansL=ansR=null;
			return;
		}
		if(val<u->key)
			Split(val,u->lch,ansL,u->lch),ansR=u;
		else
			Split(val,u->rch,u->rch,ansR),ansL=u;
		u->Update();
	}
	void Insert(int val)
	{
		Node *l,*n,*r;
		Split(val,root,l,r);
		n=NewNode(val);
		root=Merge(Merge(l,n),r);
	}
	void Delete(int val)
	{
		Node *l,*n,*r;
		Split(val-1,root,l,r);
		Split(val,r,n,r);
		Merge(l,Merge(Merge(n->lch,n->rch),r));
	}
	int GetRank(int val)
	{
		int ret=0;
		Node *u=root;
		while(u!=null)
		{
			if(u->key<val)
			{
				ret+=u->lch->siz+1;
				u=u->rch;
			}
			else
				u=u->lch;
		}
		return ret;
	}
}

struct Edge
{
	int v,c;
	Edge *nxt;
};
Edge *V[MAXN],E[MAXN*2],*cur;
void add_edge(int u,int v,int c)
{
	cur->v=v;cur->c=c;
	cur->nxt=V[u];
	V[u]=cur++;
	cur->v=u;cur->c=c;
	cur->nxt=V[v];
	V[v]=cur++;
}

int cnt[MAXN],val[MAXN];
bool vis[MAXN];
void dfs(int u,int pa=0)
{
	cnt[u]=1;
	val[u]=0;
	for(Edge *p=V[u];p;p=p->nxt)
		if(p->v!=pa&&vis[p->v]==false)
		{
			dfs(p->v,u);
			cnt[u]+=cnt[p->v];
			val[u]=max(val[u],cnt[p->v]);
		}
}
void dfs2(int n,int u,int &res,int &best,int pa=0)
{
	val[u]=max(val[u],n-cnt[u]);
	if(val[u]<best)
	{best=val[u];res=u;}
	for(Edge *p=V[u];p;p=p->nxt)
		if(p->v!=pa&&vis[p->v]==false)
			dfs2(n,p->v,res,best,u);
}
int find_center(int n,int u)
{
	dfs(u);
	int res=0,best=0x7FFFFFFF;
	dfs2(cnt[u],u,res,best);
	return res;
}

int ds[MAXN],tot;

int dfs3(int u,int k,int pa,int dis)
{
	if(dis>k)return 0;
	int res=0;
	res+=Treap::GetRank(k-dis+1);
	ds[++tot]=dis;
	for(Edge *p=V[u];p;p=p->nxt)
		if(p->v!=pa&&vis[p->v]==false)
			res+=dfs3(p->v,k,u,dis+p->c);
	return res;
}

int que[MAXN],head,tail;

int solve(int n,int k)
{
	int res=0;
	head=tail=1;
	que[1]=1;
	memset(vis+1,0,sizeof(bool)*n);
	while(head<=tail)
	{
		int u=que[head];
		head++;
		int g=find_center(n,u);
		Treap::Clear();
		Treap::Insert(0);
		for(Edge *p=V[g];p;p=p->nxt)
			if(vis[p->v]==false)
			{
				tot=0;
				res+=dfs3(p->v,k,g,p->c);
				que[++tail]=p->v;
				for(int i=1;i<=tot;i++)
					Treap::Insert(ds[i]);
			}
		vis[g]=1;
	}
	return res;
}

int main()
{
	int n,k,u,v,c;
	while(true)
	{
		scanf("%d%d",&n,&k);
		if(n==0&&k==0)break;
		cur=E;
		memset(V+1,0,sizeof(Edge*)*n);
		for(int i=1;i<n;i++)
		{
			scanf("%d%d%d",&u,&v,&c);
			add_edge(u,v,c);
		}
		printf("%d\n",solve(n,k));
	}
	return 0;
}
