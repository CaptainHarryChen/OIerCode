#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=2*1024*1024+32,INF=0x7FFFFFFF;

struct Node
{
	char val;
	int siz;
	bool flip;
	Node *ch[2],*fa;
};

Node nodes[MAXN],*null,*root,*ncnt;
void Init()
{
	null=nodes;
	null->ch[0]=null->ch[1]=null->fa=null;
	root=null;
	ncnt=nodes+1;
}
Node *NewNode(char val)
{
	ncnt->val=val;
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
}
void PushUp(Node *u)
{u->siz=1+u->ch[0]->siz+u->ch[1]->siz;}

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

Node *MakeTree(const char *A,int l,int r)
{
	if(l==r)
		return NewNode(A[l]);
	int mid=(l+r)/2;
	Node *u=NewNode(A[mid]);
	if(l<mid)
	{
		u->ch[0]=MakeTree(A,l,mid-1);
		u->ch[0]->fa=u;
	}
	if(mid<r)
	{
		u->ch[1]=MakeTree(A,mid+1,r);
		u->ch[1]->fa=u;
	}
	PushUp(u);
	return u;
}
Node *GetKthNode(int k)
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
	Node *u=GetKthNode(a);
	Splay(u);
	Node *l=GetNear(u,0);
	Node *v=GetKthNode(b);
	Splay(v);
	Node *r=GetNear(v,1);
	Splay(l);
	Splay(r,l);
	PushDown(root);
	PushDown(root->ch[0]);
	rtf=root->ch[1];
	rt=rtf->ch[0];
}

void Insert(const char S[],int a,int b,int k)
{
	Node *n=MakeTree(S,a,b),*u,*v;
	GetSection(k+1,k,u,v);
	v->ch[0]=n;
	n->fa=v;
	Splay(n);
}
void Delete(int a,int b)
{
	Node *u,*v;
	GetSection(a,b,u,v);
	v->ch[0]=null;
	Splay(v);
}
void Rotate(int a,int b)
{
	Node *u,*v;
	GetSection(a,b,u,v);
	u->flip^=1;
	Splay(u);
}

char str[MAXN];

int main()
{
	int Q,cur=0;
	char op[20];
	Init();
	str[0]=26;str[1]=27;
	root=MakeTree(str,0,1);
	scanf("%d%*c",&Q);
	for(int i=1,n;i<=Q;i++)
	{
		scanf("%s%*c",op);
		switch(op[0])
		{
			case 'M':
				scanf("%d%*c",&cur);
				break;
			case 'I':
				scanf("%d%*c",&n);
				gets(str);
				Insert(str,0,n-1,cur);
				break;
			case 'D':
				scanf("%d%*c",&n);
				Delete(cur+1,cur+n);
				break;
			case 'R':
				scanf("%d%*c",&n);
				Rotate(cur+1,cur+n);
				break;
			case 'G':
				printf("%c\n",GetKthNode(cur+1)->val);
				break;
			case 'N':
				cur++;
				break;
			case 'P':
				cur--;
				break;
		}
	}
	return 0;
}
