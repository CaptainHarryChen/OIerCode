#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200005,INF=0x7FFFFFFF;

template<class T>
void Read(T &x)
{
	char c;
	bool f=0;
	while(c=getchar(),c!=EOF)
	{
		if(c=='-')
			f=1;
		else if(c>='0'&&c<='9')
		{
			x=c-'0';
			while(c=getchar(),c>='0'&&c<='9')
				x=x*10+c-'0';
			if(f)
				x=-x;
			return;
		}
	}
}

struct Node
{
	int val,add,mn,siz;
	bool flip;
	Node *ch[2],*fa;
};

Node nodes[MAXN],*null,*root,*ncnt;
void Init()
{
	null=nodes;
	null->ch[0]=null->ch[1]=null->fa=null;
	null->mn=INF;
	root=null;
	ncnt=nodes+1;
}
Node *NewNode(int val)
{
	ncnt->val=ncnt->mn=val;
	ncnt->ch[0]=ncnt->ch[1]=ncnt->fa=null;
	ncnt->siz=1;
	return ncnt++;
}

void PushDown(Node *u)
{
	if(u->flip)
	{
		swap(u->ch[0],u->ch[1]);
		if(u->ch[0]!=null)u->ch[0]->flip^=1;
		if(u->ch[1]!=null)u->ch[1]->flip^=1;
		u->flip=0;
	}
	if(u->ch[0]!=null)
		u->ch[0]->add+=u->add,u->ch[0]->val+=u->add,u->ch[0]->mn+=u->add;
	if(u->ch[1]!=null)
		u->ch[1]->add+=u->add,u->ch[1]->val+=u->add,u->ch[1]->mn+=u->add;
	u->add=0;
}
void PushUp(Node *u)
{
	u->siz=1+u->ch[0]->siz+u->ch[1]->siz;
	u->mn=u->val;
	u->mn=min(u->mn,u->ch[0]->mn);
	u->mn=min(u->mn,u->ch[1]->mn);
}

void Rotate(Node *u)
{
	Node *v=u->fa;
	PushDown(v);
	PushDown(u);
	int d=v->ch[1]==u;
	
	u->fa=v->fa;
	if(v->fa!=null)
		v->fa->ch[v->fa->ch[1]==v]=u;
		
	v->ch[d]=u->ch[d^1];
	if(u->ch[d^1]!=null)
		u->ch[d^1]->fa=v;
	
	u->ch[d^1]=v;
	v->fa=u;
	
	if(root==v)
		root=u;
	PushUp(v);
	PushUp(u);
}
void Splay(Node *u,Node *rt=null)
{
	while(true)
	{
		Node *v=u->fa;
		Node *w=v->fa;
		PushDown(w);
		PushDown(v);
		PushDown(u);
		if(v==rt)break;
		if(w==rt)
		{
			Rotate(u);
			break;
		}
		else
		{
			if((w->ch[1]==v)==(v->ch[1]==u))
				Rotate(v),Rotate(u);
			else
				Rotate(u),Rotate(u);
		}
	}
	PushUp(u);
}
Node *GetNear(Node *u,int f)
{
	PushDown(u);
	u=u->ch[f];
	if(u==null)
		return u;
	f^=1;
	PushDown(u);
	while(u->ch[f]!=null)
		u=u->ch[f],PushDown(u);
	return u;
}

void MakeTree(int A[],int l,int r,Node *&u=root)
{
	if(l==r)
	{
		u=NewNode(A[l]);
		return;
	}
	int mid=(l+r)/2;
	u=NewNode(A[mid]);
	if(l<mid)
	{
		MakeTree(A,l,mid-1,u->ch[0]);
		u->ch[0]->fa=u;
	}
	if(mid<r)
	{
		MakeTree(A,mid+1,r,u->ch[1]);
		u->ch[1]->fa=u;
	}
	PushUp(u);
}
Node *GetKthNum(int k)
{
	Node *u=root;
	int r;
	while(u!=null)
	{
		PushDown(u);
		r=u->ch[0]->siz;
		if(r==k)
			break;
		if(r<k)
		{
			k-=r+1;
			u=u->ch[1];
		}
		else
			u=u->ch[0];
	}
	return u;
}
void GetSection(int a,int b,Node *&rt,Node *&rtf)
{
	Node *u=GetKthNum(a);
	Splay(u);
	Node *l=GetNear(u,0);
	Node *v=GetKthNum(b);
	Splay(v);
	Node *r=GetNear(v,1);
	Splay(l);
	Splay(r,l);
	PushDown(root);
	PushDown(root->ch[0]);
	rtf=root->ch[1];
	rt=rtf->ch[0];
}

void Add(int a,int b,int ad)
{
	Node *u,*v;
	GetSection(a,b,u,v);
	u->add+=ad;u->val+=ad;u->mn+=ad;
	Splay(u);
}
void Reverse(int a,int b)
{
	Node *u,*v;
	GetSection(a,b,u,v);
	u->flip^=1;
	Splay(u);
}
void Revolve(int a,int b,int T)
{
	T=(T%(b-a+1)+(b-a+1))%(b-a+1);
	if(T==0)return;
	Node *rt,*rtf,*u;
	GetSection(a,b,rt,rtf);
	
	u=GetKthNum(b-T+1);
	Splay(u,rtf);
	Node *l=GetNear(u,0);
	
	Splay(l,rtf);
	Splay(u,l);
	PushDown(l);
	l->ch[1]=null;
	u->fa=null;
	PushUp(l);
	
	Node *v=GetKthNum(a);
	Splay(v,rtf);
	PushDown(v);
	v->ch[0]=u;
	u->fa=v;
	PushUp(v);
}
void Insert(int a,int P)
{
	Node *u,*v;
	GetSection(a+1,a,u,v);
	PushDown(v);
	v->ch[0]=NewNode(P);
	v->ch[0]->fa=v;
	Splay(v);
}
void Delete(int a)
{
	Node *u,*v;
	GetSection(a,a,u,v);
	PushDown(v);
	v->ch[0]=null;
	Splay(v);
}
int Min(int a,int b)
{
	Node *u,*v;
	GetSection(a,b,u,v);
	return u->mn;
}

int A[MAXN];
int main()
{
	int n,m,x,y,D,P,T;
	char op[10];
	Init();
	Read(n);
	for(int i=1;i<=n;i++)
		Read(A[i]);
	A[0]=INF;A[n+1]=INF;
	MakeTree(A,0,n+1);
	Read(m);
	for(int i=1;i<=m;i++)
	{
		scanf("%s",op);
		if(strcmp(op,"ADD")==0)
		{
			Read(x);Read(y);Read(D);
			Add(x,y,D);
		}
		else if(strcmp(op,"REVERSE")==0)
		{
			Read(x);Read(y);
			Reverse(x,y);
		}
		else if(strcmp(op,"REVOLVE")==0)
		{
			Read(x);Read(y);Read(T);
			Revolve(x,y,T);
		}
		else if(strcmp(op,"INSERT")==0)
		{
			Read(x);Read(P);
			Insert(x,P);
		}
		else if(strcmp(op,"DELETE")==0)
		{
			Read(x);
			Delete(x);
		}
		else if(strcmp(op,"MIN")==0)
		{
			Read(x);Read(y);
			printf("%d\n",Min(x,y));
		}
	}
	return 0;
}
