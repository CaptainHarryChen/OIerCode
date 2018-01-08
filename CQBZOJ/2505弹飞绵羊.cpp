#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005;

struct Node *null;
struct Node
{
	int siz;
	bool rev;
	Node *fa,*ch[2];
	Node(){siz=1;rev=false;fa=ch[0]=ch[1]=null;}
	bool IsRoot()
	{return fa==null||(fa->ch[0]!=this&&fa->ch[1]!=this);}
	void SetChild(Node *u,int d)
	{
		ch[d]=u;
		if(u!=null)
			u->fa=this;
	}
	int dir()
	{return fa->ch[1]==this;}
	void PushUp()
	{siz=1+ch[0]->siz+ch[1]->siz;}
	void PushDown()
	{
		if(rev)
		{
			swap(ch[0],ch[1]);
			if(ch[0]!=null)ch[0]->rev^=1;
			if(ch[1]!=null)ch[1]->rev^=1;
			rev=false;
		}
	}
};
Node nodes[MAXN];

void Init()
{
	null=nodes;
	null->siz=0;null->rev=false;
	null->fa=null->ch[0]=null->ch[1]=null;
}

void Rotate(Node *u)
{
	Node *v=u->fa;
	v->PushDown();
	u->PushDown();
	int d=u->dir();
	if(v->IsRoot())
		u->fa=v->fa;
	else
		v->fa->SetChild(u,v->dir());
	v->SetChild(u->ch[d^1],d);
	u->SetChild(v,d^1);
	v->PushUp();
	u->PushUp();
}
void Splay(Node *u)
{
	while(!u->IsRoot())
	{
		Node *v=u->fa;
		v->PushDown();
		if(v->IsRoot())
			Rotate(u);
		else
		{
			v->fa->PushDown();
			if(u->dir()==v->dir())
				Rotate(v);
			else
				Rotate(u);
			Rotate(u);
		}
	}
	u->PushUp();
}
void Access(Node *u)
{
	Node *v=null;
	while(u!=null)
	{
		Splay(u);
		u->PushDown();
		u->SetChild(v,1);
		u->PushUp();
		v=u;
		u=u->fa;
	}
}

void MakeRoot(Node *u)
{
	Access(u);
	Splay(u);
	u->rev^=1;
}
void Link(Node *u,Node *v)
{
	MakeRoot(u);
	u->fa=v;
}
void Cut(Node *u,Node *v)
{
	MakeRoot(u);
	Access(v);
	Splay(v);
	v->ch[0]=null;
	u->fa=null;
}

int fa[MAXN];
int main()
{
	int n,m,k,op;
	scanf("%d",&n);
	Init();
	for(int i=1;i<=n+1;i++)
		nodes[i]=Node();
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&k);
		fa[i]=min(i+k,n+1);
		nodes[i].fa=nodes+fa[i];
	}
	scanf("%d",&m);
	for(int q=1,i,j;q<=m;q++)
	{
		scanf("%d%d",&op,&i);
		i++;
		if(op==1)
		{
			MakeRoot(nodes+n+1);
			Access(nodes+i);
			printf("%d\n",nodes[i].siz-1);
		}
		else
		{
			scanf("%d",&j);
			Cut(nodes+i,nodes+fa[i]);
			fa[i]=min(i+j,n+1);
			Link(nodes+i,nodes+fa[i]);
		}
	}
	return 0;
}
