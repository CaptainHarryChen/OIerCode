#include<cstdio>
#include<algorithm>
using namespace std;
const unsigned int MAXN=100005,MOD=51061;

struct Node *null;
struct Node
{
	unsigned int val,sum,siz;
	unsigned int times,add;
	bool rev;
	Node *fa,*ch[2];
	Node(){fa=ch[0]=ch[1]=null;siz=times=1;sum=val=1;add=0;rev=false;}
	unsigned int dir()
	{return fa->ch[1]==this;}
	bool isRoot()
	{return fa==null||(fa->ch[0]!=this&&fa->ch[1]!=this);}
	void setChild(Node *c,unsigned int d)
	{
		ch[d]=c;
		if(c!=null)
			c->fa=this;
	}
	void pushUp()
	{
		sum=(ch[0]->sum+ch[1]->sum+val)%MOD;
		siz=ch[0]->siz+ch[1]->siz+1;
	}
	void Update(int ad,int ti)
	{
		if(this==null)
			return;
		val=(val*ti)%MOD;
		sum=(sum*ti)%MOD;
		times=(times*ti)%MOD;
		add=(add*ti)%MOD;
		val=(val+ad)%MOD;
		sum=(sum+siz*ad)%MOD;
		add=(add+ad)%MOD;
	}
	void pushDown()
	{
		if(rev)
		{
			swap(ch[0],ch[1]);
			if(ch[0]!=null)
				ch[0]->rev^=1;
			if(ch[1]!=null)
				ch[1]->rev^=1;
			rev=false;
		}
		ch[0]->Update(add,times);
		ch[1]->Update(add,times);
		add=0;times=1;
	}
};

Node node[MAXN],*id[MAXN];
void Init(unsigned int n)
{
	null=node;
	null->fa=null->ch[0]=null->ch[1]=null;
	null->sum=null->val=null->siz=0;
	for(unsigned int i=1;i<=n;i++)
	{
		node[i]=Node();
		id[i]=node+i;
	}
}

void Rotate(Node *u)
{
	Node *v=u->fa;
	v->pushDown();
	u->pushDown();
	unsigned int d=u->dir();
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
void makeRoot(Node *u)
{
	Access(u);
	Splay(u);
	u->rev^=1;
}
void Link(Node *u,Node *v)
{
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
	u->setChild(null,1);
	v->fa=null;
}
void Add(Node *u,Node *v,unsigned int add)
{
	makeRoot(u);
	Access(v);
	Splay(u);
	u->Update(add,1);
}
void Mul(Node *u,Node *v,unsigned int times)
{
	makeRoot(u);
	Access(v);
	Splay(u);
	u->Update(0,times);
}
unsigned int Query(Node *u,Node *v)
{
	makeRoot(u);
	Access(v);
	Splay(u);
	u->pushDown();
	return u->sum;
}

int main()
{
	unsigned int n,q;
	scanf("%u%u",&n,&q);
	Init(n);
	for(unsigned int i=1,u,v;i<n;i++)
	{
		scanf("%u%u",&u,&v);
		Link(id[u],id[v]);
	}
	char op[4];
	for(unsigned int i=1,u,v,c,u1,v1,u2,v2;i<=q;i++)
	{
		scanf("%s",op);
		if(op[0]=='+')
		{
			scanf("%u%u%u",&u,&v,&c);
			Add(id[u],id[v],c);
		}
		else if(op[0]=='-')
		{
			scanf("%u%u%u%u",&u1,&v1,&u2,&v2);
			Cut(id[u1],id[v1]);
			Link(id[u2],id[v2]);
		}
		else if(op[0]=='*')
		{
			scanf("%u%u%u",&u,&v,&c);
			Mul(id[u],id[v],c);
		}
		else if(op[0]=='/')
		{
			scanf("%u%u",&u,&v);
			printf("%u\n",Query(id[u],id[v]));
		}
	}
	
	return 0;
}
