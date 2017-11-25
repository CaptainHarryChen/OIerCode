#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005;

struct Node
{
	int fa,dep;
	Node *lch,*rch;
};
Node nodes[MAXN*50],*rt[MAXN],*cur,*null;
int maxnum;
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
	null=nodes;
	null->lch=null->rch=null;
	cur=nodes+1;
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
void Union(Node *&now,Node *old,int a,int b)
{
	Node *ra,*rb;
	ra=Root(old,a);
	rb=Root(old,b);
	if(ra==rb)return;
	if(ra->dep<rb->dep)
		swap(ra,rb);
	*now=*old;
	Modify(now,rb->fa,ra->fa);
	if(ra->dep==rb->dep)
	{
		Node *t=Query(now,ra->fa);
		t->dep++;
	}
}
bool check(Node *vers,int x,int y)
{return Root(vers,x)==Root(vers,y);}

int main()
{
	int n,m,op,a,b,k;
	scanf("%d%d",&n,&m);
	Init(n);
	int lastans=0,latest=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d",&a,&b);
			a^=lastans;b^=lastans;
			rt[i]=rt[latest];
			Union(rt[i],rt[latest],a,b);
			latest=i;
		}
		else if(op==2)
		{
			scanf("%d",&k);
			k^=lastans;
			latest=k;
			rt[i]=rt[latest];
		}
		else
		{
			scanf("%d%d",&a,&b);
			a^=lastans;b^=lastans;
			rt[i]=rt[latest];
			lastans=check(rt[i],a,b);
			printf("%d\n",lastans);
		}
	}
	return 0;
}
