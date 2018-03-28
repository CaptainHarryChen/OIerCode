#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=50005;

struct Node *null;
struct Node
{
	long long val,exp,sum,s1,s2;
	int siz;
	int add;
	bool rev;
	Node *fa,*ch[2];
	Node()
	{fa=ch[0]=ch[1]=null;siz=1;sum=s1=s2=exp=val=add=0;rev=false;}
	Node(int a)
	{fa=ch[0]=ch[1]=null;siz=1;sum=exp=val=s1=s2=a;add=0;rev=false;}
	int dir()
	{return fa->ch[1]==this;}
	bool isRoot()
	{return fa==null||(fa->ch[0]!=this&&fa->ch[1]!=this);}
	void setChild(Node *c,int d)
	{
		ch[d]=c;
		if(c!=null)
			c->fa=this;
	}
	void pushUp()
	{
		sum=ch[0]->sum+ch[1]->sum+val;
		s1=ch[0]->s1+val*(ch[0]->siz+1)+ch[1]->sum*(ch[0]->siz+1)+ch[1]->s1;
		s2=ch[1]->s2+val*(ch[1]->siz+1)+ch[0]->sum*(ch[1]->siz+1)+ch[0]->s2;
		exp=ch[0]->exp+ch[0]->s1*(ch[1]->siz+1)+val*(ch[0]->siz+1)*(ch[1]->siz+1)+ch[1]->exp+ch[1]->s2*(ch[0]->siz+1);
		siz=ch[0]->siz+ch[1]->siz+1;
	}
	void Update(int ad,bool re)
	{
		if(this==null)
			return;
		if(re)
		{
			swap(ch[0],ch[1]);
			swap(s1,s2);
			rev^=1;
		}
		add+=1LL*ad;
		val+=1LL*ad;
		sum+=1LL*ad*siz;
		s1+=1LL*ad*siz*(siz+1)/2;
		s2+=1LL*ad*siz*(siz+1)/2;
		exp+=1LL*ad*siz*(siz+1)*(siz+2)/6;
	}
	void pushDown()
	{
		ch[0]->Update(add,rev);
		ch[1]->Update(add,rev);
		add=0;
		rev=false;
	}
};

Node node[MAXN],*id[MAXN];
void Init(int A[],int n)
{
	null=node;
	null->fa=null->ch[0]=null->ch[1]=null;
	null->siz=0;
	for(int i=1;i<=n;i++)
	{
		node[i]=Node(A[i]);
		id[i]=node+i;
	}
}

void Rotate(Node *u)
{
	Node *v=u->fa;
	v->pushDown();
	u->pushDown();
	int d=u->dir();
	if(!v->isRoot())
		v->fa->setChild(u,v->dir());
	else
		u->fa=v->fa;
	v->setChild(u->ch[d^1],d);
	u->setChild(v,d^1);
	v->pushUp();
	u->pushUp();
}
void Splay(Node *u)
{
	while(!u->isRoot())
	{
		Node *v=u->fa;
		if(v->isRoot())
		{
			Rotate(u);
			break;
		}
		Node *w=v->fa;
		w->pushDown();
		v->pushDown();
		if(u->dir()==v->dir())
			Rotate(v);
		else
			Rotate(u);
		Rotate(u);
	}
}
void Access(Node *u)
{
	Node *last=null;
	while(u!=null)
	{
		Splay(u);
		u->pushDown();
		u->setChild(last,1);
		u->pushUp();
		last=u;
		u=u->fa;
	}
}
Node *findRoot(Node *u)
{
	Access(u);
	Splay(u);
	u->pushDown();
	while(u->ch[0]!=null)
	{
		u=u->ch[0];
		u->pushDown();
	}
	return u;
}
bool Connected(Node *u,Node *v)
{
	return findRoot(u)==findRoot(v);
}
void makeRoot(Node *u)
{
	Access(u);
	Splay(u);
	u->Update(0,true);
}
void Link(Node *u,Node *v)
{
	if(Connected(u,v))
		return;
	makeRoot(u);
	makeRoot(v);
	v->fa=u;
}
void Cut(Node *u,Node *v)
{
	makeRoot(u);
	Access(v);
	Splay(u);
	u->pushDown();
	if(u->ch[1]!=v||u->ch[1]->siz!=1)
		return;
	u->setChild(null,1);
	v->fa=null;
}
void Add(Node *u,Node *v,int add)
{
	if(!Connected(u,v))
		return;
	makeRoot(u);
	Access(v);
	Splay(u);
	u->Update(add,false);
}
long long gcd(long long a,long long b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}
pair<long long,long long> Query(Node *u,Node *v)
{
	if(!Connected(u,v))
		return make_pair(-1,1);
	makeRoot(u);
	Access(v);
	Splay(u);
	u->pushDown();
	u->pushUp();
	long long g=gcd(u->exp,1LL*u->siz*(u->siz+1)/2LL);
	return make_pair(u->exp/g,1LL*u->siz*(u->siz+1)/2LL/g);
}

int a[MAXN];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	Init(a,n);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		Link(id[u],id[v]);
	}
	int op,u,v,d;
	pair<long long,long long> res;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&op,&u,&v);
		if(op==1)
			Cut(id[u],id[v]);
		if(op==2)
			Link(id[u],id[v]);
		if(op==3)
		{
			scanf("%d",&d);
			Add(id[u],id[v],d);
		}
		if(op==4)
		{
			res=Query(id[u],id[v]);
			if(res.first==-1)
				puts("-1");
			else
				printf("%lld/%lld\n",res.first,res.second);
		}
	}
	return 0;
}
