#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005;

struct Node
{
	Node *lch,*rch;
	int fa,dep;
};
int opcnt,maxnum;
Node nodes[MAXN*20],*cur,*null;
Node *rt[MAXN];
void Build(Node *&u,int l=1,int r=maxnum)
{
	if(u==null)
	{
		u=cur++;
		u->lch=u->rch=null;
		u->fa=u->dep=0;
	}
	if(l==r)
	{
		u->fa=l;
		u->dep=1;
		return;
	}
	int mid=(l+r)/2;
	Build(u->lch,l,mid);
	Build(u->rch,mid+1,r);
}
void Init(int mx)
{
	maxnum=mx;
	cur=nodes+1;
	null=nodes;
	nodes[0].lch=nodes[0].rch=null;
	opcnt=0;
	rt[0]=null;
	Build(rt[0]);
}
void Modify(Node *&u,int pos,int nfa,int l=1,int r=maxnum)
{
	*cur=*u;
	u=cur++;
	if(l==r)
	{
		u->fa=nfa;
		return;
	}
	int mid=(l+r)/2;
	if(pos<=mid)
		Modify(u->lch,pos,nfa,l,mid);
	else
		Modify(u->rch,pos,nfa,mid+1,r);
}
Node *Query(Node *u,int pos,int l=1,int r=maxnum)
{
	if(l==r)
		return u;
	int mid=(l+r)/2;
	if(pos<=mid)
		return Query(u->lch,pos,l,mid);
	return Query(u->rch,pos,mid+1,r);
}
Node *Root(Node *vers,int x)
{
	Node *t;
	while(t=Query(vers,x),t->fa!=x)
		x=t->fa;
	return t;
}
void Union(Node *&now,Node *old,int x,int y)
{
	Node *rx,*ry;
	rx=Root(old,x);
	ry=Root(old,y);
	if(rx->dep<ry->dep)
		swap(rx,ry);
	*now=*old;
	Modify(now,ry->fa,rx->fa);
	if(rx->dep==ry->dep)
	{
		Node *t=Query(now,rx->fa);
		t->dep++;
	}
}
bool check(Node *vers,int x,int y)
{return Root(vers,x)==Root(vers,y);}

int main()
{
	int n,m,op,a,b;
	scanf("%d%d",&n,&m);
	int latest=0;
	Init(n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d",&a,&b);
			rt[i]=rt[latest];
			Union(rt[i],rt[latest],a,b);
			latest=i;
		}
		else if(op==2)
		{
			scanf("%d",&a);
			latest=a;
			rt[i]=rt[latest];
		}
		else
		{
			scanf("%d%d",&a,&b);
			rt[i]=rt[latest];
			printf("%d\n",check(rt[i],a,b));
		}
	}
	return 0;
}
