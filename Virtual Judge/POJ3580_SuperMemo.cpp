#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200005,INF=0x7F7F7F7F;

struct Node *null;
struct Node
{
	int val;
	int siz;
	int add;
	int mn;
	bool rev;
	Node *fa,*ch[2];
	Node(){}
	Node(int value)
	{mn=val=value;add=0;siz=1;rev=false;fa=ch[0]=ch[1]=null;}
	int Dir()
	{return fa->ch[1]==this;}
	void SetChild(Node *child,int Dir)
	{
		ch[Dir]=child;
		if(child!=null)
			child->fa=this;
	}
	void PushUp()
	{
		siz=ch[0]->siz+1+ch[1]->siz;
		mn=min(val,min(ch[0]->mn,ch[1]->mn));
	}
	void PushDown()
	{
		if(ch[0]!=null)
		{
			ch[0]->add+=add;
			ch[0]->mn+=add;
			ch[0]->val+=add;
		}
		if(ch[1]!=null)
		{
			ch[1]->add+=add;
			ch[1]->mn+=add;
			ch[1]->val+=add;
		}
		add=0;
		if(rev)
		{
			swap(ch[0],ch[1]);
			if(ch[0]!=null)ch[0]->rev^=1;
			if(ch[1]!=null)ch[1]->rev^=1;
			rev=false;
		}
	}
};

Node nodes[MAXN],*ncnt,*root;

void Init()
{
	null=nodes;
	*null=Node(INF);
	null->siz=0;
	ncnt=nodes+1;
	root=null;
}
Node *NewNode(int val)
{
	*ncnt=Node(val);
	return ncnt++;
}

void Rotate(Node *u)
{
	Node *v=u->fa;
	v->PushDown();
	u->PushDown();
	int d=u->Dir();
	
	if(v->fa!=null)
		v->fa->SetChild(u,v->Dir());
	else
		u->fa=null;
	
	v->SetChild(u->ch[d^1],d);
	u->SetChild(v,d^1);
	
	if(root==v)
		root=u;
	
	v->PushUp();
	u->PushUp();
}
void Splay(Node *u,Node *rt=null)
{
	while(u!=null)
	{
		Node *v=u->fa;
		if(v==rt)
			break;
		Node *w=v->fa;
		if(w==rt)
		{
			Rotate(u);
			break;
		}
		w->PushDown();
		v->PushDown();
		if(u->Dir()==v->Dir())
			Rotate(v);
		else
			Rotate(u);
		Rotate(u);
	}
}
void Build(int a[],int l,int r)
{
	root=NewNode(a[l]);
	Node *u=root;
	for(int i=1;i<=r;i++)
	{
		u->SetChild(NewNode(a[i]),1);
		u=u->ch[1];
	}
	for(int i=r;i>l;i--)
	{
		u=u->fa;
		u->PushUp();
	}
}

Node *FindKth(int k)
{
	if(k>root->siz)
		return null;
	Node *u=root;
	while(u!=null)
	{
		u->PushDown();
		int rank=u->ch[0]->siz;
		if(rank==k)
			return u;
		else if(rank<k)
		{
			k-=rank+1;
			u=u->ch[1];
		}
		else
			u=u->ch[0];
	}
	return null;
}
Node *SelectSection(int x,int y)
{
	Node *l=FindKth(x-1);Splay(l);
	Node *r=FindKth(y+1);Splay(r,l);
	r->PushDown();
	return r->ch[0];
}

void Add(int x,int y,int D)
{
	Node *sec=SelectSection(x,y);
	sec->add+=D;
	sec->mn+=D;
	sec->val+=D;
	Splay(sec);
}
void Reverse(int x,int y)
{
	Node *sec=SelectSection(x,y);
	sec->rev^=1;
	Splay(sec);
}
void Revolve(int x,int y,int T)
{
	T%=(y-x+1);
	T=(T+y-x+1)%(y-x+1);
	if(T==0)return;
	Reverse(x,y);
	Reverse(x,x+T-1);
	Reverse(x+T,y);
}
void Insert(int x,int P)
{
	Node *u,*v,*nw=NewNode(P);
	if(root==null)
	{
		root=nw;
		return;
	}
	u=FindKth(x);Splay(u);
	v=FindKth(x+1);Splay(v,u);
	v->PushDown();
	v->SetChild(nw,0);
	Splay(nw);
}
void Delete(int x)
{
	Node *u=SelectSection(x,x),*v=u->fa;
	v->PushDown();
	v->SetChild(null,0);
	Splay(v);
}
int Min(int x,int y)
{
	Node *sec=SelectSection(x,y);
	int ans=sec->mn;
	Splay(sec);
	return ans;
}

int a[MAXN];
int main()
{
	int n,m;
	char op[10];
	scanf("%d",&n);
	Init();
	a[0]=INF;a[n+1]=INF;
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	Build(a,0,n+1);
	scanf("%d",&m);
	for(int i=1,x,y,T,P,D;i<=m;i++)
	{
		scanf("%s",op);
		if(strcmp(op,"ADD")==0)
		{
			scanf("%d%d%d",&x,&y,&D);
			Add(x,y,D);
		}
		else if(strcmp(op,"REVERSE")==0)
		{
			scanf("%d%d",&x,&y);
			Reverse(x,y);
		}
		else if(strcmp(op,"REVOLVE")==0)
		{
			scanf("%d%d%d",&x,&y,&T);
			Revolve(x,y,T);
		}
		else if(strcmp(op,"INSERT")==0)
		{
			scanf("%d%d",&x,&P);
			Insert(x,P);
		}
		else if(strcmp(op,"DELETE")==0)
		{
			scanf("%d",&x);
			Delete(x);
		}
		else if(strcmp(op,"MIN")==0)
		{
			scanf("%d%d",&x,&y);
			printf("%d\n",Min(x,y));
		}
	}
	return 0;
}
