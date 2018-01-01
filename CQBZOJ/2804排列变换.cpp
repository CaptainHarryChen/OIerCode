#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;

struct Node
{
	int key,siz;
	bool flip;
	Node *ch[2],*fa;
};

Node nodes[MAXN],*root,*ncnt,*null;
void Update(Node *u)
{u->siz=1+u->ch[0]->siz+u->ch[1]->siz;}
void Flip(Node *u)
{
	if(u->flip)
	{
		swap(u->ch[0],u->ch[1]);
		if(u->ch[0]!=null)u->ch[0]->flip^=1;
		if(u->ch[1]!=null)u->ch[1]->flip^=1;
		u->flip=0;
	}
}
void Init()
{
	null=nodes;
	null->ch[0]=null->ch[1]=null->fa=null;
	root=null;
	ncnt=nodes+1;
}
Node *NewNode(int val)
{
	ncnt->key=val;
	ncnt->siz=1;
	ncnt->ch[0]=ncnt->ch[1]=ncnt->fa=null;
	return ncnt++;
}

void Rotate(Node *u)
{
	Node *v=u->fa;
	Flip(v);Flip(u);
	int d=v->ch[1]==u;
	
	u->fa=v->fa;
	if(v->fa!=null)
		v->fa->ch[v->fa->ch[1]==v]=u;
	
	v->ch[d]=u->ch[d^1];
	if(u->ch[d^1]!=null)
		u->ch[d^1]->fa=v;
	
	u->ch[d^1]=v;
	v->fa=u;
	
	if(v==root)
		root=u;
	Update(v);
	Update(u);
}
void Splay(Node *u,Node *rt=null)
{
	while(true)
	{
		Node *v=u->fa;
		Node *w=v->fa;
		Flip(w);Flip(v);Flip(u);
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
	Update(u);
}
Node *GetNear(Node *u,int t)
{
	Flip(u);
	u=u->ch[t];
	if(u==null)return null;
	Flip(u);
	while(u->ch[t^1]!=null)
	{
		u=u->ch[t^1];
		Flip(u);
	}
	return u;
}

void Insert(int val)
{
	if(root==null)
	{
		root=NewNode(val);
		return;
	}
	Node *u=root;
	int d;
	while(true)
	{
		d=(val>u->key);
		Flip(u);
		if(u->ch[d]==null)
			break;
		u=u->ch[d];
	}
	u->ch[d]=NewNode(val);
	u->ch[d]->fa=u;
	Splay(u);
}

Node *GetKthNum(int k)
{
	Node *u=root;
	while(u!=null)
	{
		Flip(u);
		if(u->ch[0]->siz+1==k)
			break;
		if(u->ch[0]->siz+1<k)
		{
			k-=u->ch[0]->siz+1;
			u=u->ch[1];
		}
		else
			u=u->ch[0];
	}
	Splay(u);
	return u;
}
Node *GetEnd()
{
	Node *u=root;
	while(u!=null)
	{
		Flip(u);
		if(u->ch[1]==null)
			break;
		u=u->ch[1];
	}
	Splay(u);
	return u;
}

void op(int a,int b)
{
	Node *u=GetKthNum(a),*l=GetNear(u,0);
	Node *v=GetKthNum(b),*r=GetNear(v,1);
	if(l==null&&r==null)
		root->flip^=1;
	else if(r==null)
	{
		Splay(l);
		Flip(root);
		root->ch[1]->flip^=1;
	}
	else if(l==null)
	{
		Splay(r);
		Flip(root);
		Node *t=root->ch[0];
		t->fa=null;
		t->flip^=1;
		root->ch[0]=null;
		Update(root);
		GetEnd();
		Flip(root);
		root->ch[1]=t;
		t->fa=root;
		Update(root);
	}
	else
	{
		Splay(l);
		Splay(r,l);
		Flip(root);
		Flip(root->ch[1]);
		Node *t=root->ch[1]->ch[0];
		t->fa=null;
		t->flip^=1;
		root->ch[1]->ch[0]=null;
		Update(root->ch[1]);
		Update(root);
		GetEnd();
		Flip(root);
		root->ch[1]=t;
		t->fa=root;
		Update(root);
	}
}
void print(Node *u=root)
{
	if(u==null)return;
	Flip(u);
	print(u->ch[0]);
	printf("%d\n",u->key);
	print(u->ch[1]);
}

int main()
{
	int n,m,a,b;
	scanf("%d%d",&n,&m);
	Init();
	for(int i=1;i<=n;i++)
		Insert(i);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		op(a,b);
	}
	print();
	return 0;
}
