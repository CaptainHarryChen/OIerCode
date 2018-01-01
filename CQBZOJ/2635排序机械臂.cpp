#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005,INF=0x7FFFFFFF;

struct Node
{
	int siz;
	bool flip;
	pair<int,int> key,mn;
	Node *ch[2],*fa;
};

Node nodes[MAXN],*root,*null,*ncnt;
Node *NewNode(pair<int,int> val)
{
	ncnt->siz=1;
	ncnt->key=ncnt->mn=val;
	ncnt->ch[0]=ncnt->ch[1]=ncnt->fa=null;
	return ncnt++;
}
void Init()
{
	null=nodes;
	null->mn=make_pair(INF,INF);
	null->ch[0]=null->ch[1]=null->fa=null;
	root=null;
	ncnt=nodes+1;
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
{
	u->siz=1+u->ch[0]->siz+u->ch[1]->siz;
	u->mn=u->key;
	u->mn=min(u->mn,u->ch[0]->mn);
	u->mn=min(u->mn,u->ch[1]->mn);
}

void Rotate(Node *u)
{
	Node *v=u->fa;
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
}
Node *GetNear(Node *u,int t)
{
	PushDown(u);
	u=u->ch[t];
	if(u==null)return u;
	PushDown(u);
	while(u->ch[t^1]!=null)
		u=u->ch[t^1],PushDown(u);
	return u;
}

void MakeTree(int A[],int l,int r,Node *&u=root)
{
	if(l==r)
	{
		u=NewNode(make_pair(A[l],l));
		return;
	}
	int mid=(l+r)/2;
	u=NewNode(make_pair(A[mid],mid));
	if(l<=mid-1)
	{
		MakeTree(A,l,mid-1,u->ch[0]);
		u->ch[0]->fa=u;
	}
	if(mid+1<=r)
	{
		MakeTree(A,mid+1,r,u->ch[1]);
		u->ch[1]->fa=u;
	}
	PushUp(u);
}
Node *GetKthNum(int k)
{
	Node *u=root;
	while(u!=null)
	{
		PushDown(u);
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
void DelMin()
{
	Node *u=GetKthNum(1);
	PushDown(u);
	root=u->ch[1];
	root->fa=null;
}
void Flip(Node *u)
{
	Node *r=GetNear(u,1);
	if(r==null)
	{
		u->flip^=1;
		return;
	}
	Splay(r);
	PushDown(r);
	r->ch[0]->flip^=1;
}
Node *GetMin(int &res)
{
	Node *u=root;
	PushDown(u);
	res=u->ch[0]->siz+1;
	while(u!=null)
	{
		if(u->key<u->ch[0]->mn&&u->key<u->ch[1]->mn)
			break;
		if(u->ch[0]->mn<u->ch[1]->mn)
			u=u->ch[0],PushDown(u),res-=u->ch[1]->siz+1;
		else
			u=u->ch[1],PushDown(u),res+=u->ch[0]->siz+1;
	}
	Splay(u);
	return u;
}

int A[MAXN];
int main()
{
	int n;
	Init();
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",A+i);
	MakeTree(A,1,n);
	for(int i=1,ans;i<=n;i++)
	{
		Flip(GetMin(ans));
		DelMin();
		printf("%d",ans+i-1);
		if(i!=n)putchar(' ');
	}
	puts("");
	return 0;
}
