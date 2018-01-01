#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500005,INF=10000000;

void Read(int &n)
{
	char c;
	bool flag=false;
	while(c=getchar(),c!=EOF)
	{
		if(c>='0'&&c<='9')
		{
			n=0;
			while(c>='0'&&c<='9')
				n=n*10+c-'0',c=getchar();
			if(flag)n=-n;
			return;
		}
		if(c=='-')
			flag=true;
	}
}

struct Node
{
	int val,siz,modi,sum,ls,rs,best;
	bool flip;
	Node *ch[2],*fa;
};

Node nodes[MAXN],*null,*root,*mem[MAXN];
int ncnt;

void Init()
{
	for(int i=1;i<MAXN;i++)
		mem[i]=nodes+MAXN-i;
	ncnt=MAXN-1;
	null=nodes;
	null->ch[0]=null->ch[1]=null->fa=null;
	null->modi=INF;
	null->best=null->ls=null->rs=-INF;
	root=null;
}
Node *NewNode(int val)
{
	mem[ncnt]->val=mem[ncnt]->sum=val;
	mem[ncnt]->ch[0]=mem[ncnt]->ch[1]=mem[ncnt]->fa=null;
	mem[ncnt]->siz=1;mem[ncnt]->modi=INF;
	mem[ncnt]->ls=mem[ncnt]->rs=mem[ncnt]->best=val;
	mem[ncnt]->flip=false;
	return mem[ncnt--];
}

void PushDown(Node *u)
{
	if(u->flip)
	{
		swap(u->ch[0],u->ch[1]);
		if(u->ch[0]!=null)u->ch[0]->flip^=1,swap(u->ch[0]->ls,u->ch[0]->rs);
		if(u->ch[1]!=null)u->ch[1]->flip^=1,swap(u->ch[1]->ls,u->ch[1]->rs);
		u->flip=0;
	}
	if(u->modi!=INF)
	{
		if(u->ch[0]!=null)
		{
			u->ch[0]->val=u->ch[0]->modi=u->modi;
			u->ch[0]->sum=u->modi*u->ch[0]->siz;
			u->ch[0]->ls=u->ch[0]->rs=u->ch[0]->best=max(u->modi,u->modi*u->ch[0]->siz);
		}
		if(u->ch[1]!=null)
		{
			u->ch[1]->val=u->ch[1]->modi=u->modi;
			u->ch[1]->sum=u->modi*u->ch[1]->siz;
			u->ch[1]->ls=u->ch[1]->rs=u->ch[1]->best=max(u->modi,u->modi*u->ch[1]->siz);
		}
		u->modi=INF;
	}
}
void PushUp(Node *u)
{
	u->siz=1+u->ch[0]->siz+u->ch[1]->siz;
	u->sum=u->val+u->ch[0]->sum+u->ch[1]->sum;
	u->ls=max(u->ch[0]->ls,u->ch[0]->sum+u->val);
	u->ls=max(u->ls,u->ch[0]->sum+u->val+u->ch[1]->ls);
	u->rs=max(u->ch[1]->rs,u->ch[1]->sum+u->val);
	u->rs=max(u->rs,u->ch[1]->sum+u->val+u->ch[0]->rs);
	u->best=u->val;
	u->best=max(u->best,u->ch[0]->best);
	u->best=max(u->best,u->ch[1]->best);
	u->best=max(u->best,u->ch[0]->rs+u->val);
	u->best=max(u->best,u->ch[0]->rs+u->val+u->ch[1]->ls);
	u->best=max(u->best,u->val+u->ch[1]->ls);
}

void Free(Node *u)
{
	mem[++ncnt]=u;
	if(u->ch[0]!=null)
		Free(u->ch[0]);
	if(u->ch[1]!=null)
		Free(u->ch[1]);
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

Node *MakeTree(const int A[],int l,int r)
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

void Insert(int A[],int a,int b,int k)
{
	Node *n=MakeTree(A,a,b),*u,*v;
	GetSection(k+1,k,u,v);
	v->ch[0]=n;
	n->fa=v;
	PushUp(v);
	PushUp(root);
}
void Delete(int a,int b)
{
	Node *u,*v;
	GetSection(a,b,u,v);
	v->ch[0]=null;
	Free(u);
	PushUp(v);
	PushUp(root);
}
void MakeSame(int a,int b,int c)
{
	Node *u,*v;
	GetSection(a,b,u,v);
	u->sum=c*u->siz;
	u->ls=u->rs=u->best=max(c,c*u->siz);
	u->val=u->modi=c;
	PushUp(v);
	PushUp(root);
}
void Reverse(int a,int b)
{
	Node *u,*v;
	GetSection(a,b,u,v);
	u->flip^=1;
	swap(u->ls,u->rs);
	PushUp(v);
	PushUp(root);
}
int GetSum(int a,int b)
{
	Node *u,*v;
	GetSection(a,b,u,v);
	int res=u->sum;
	return res;
}
int MaxSum()
{
	Node *u,*v;
	GetSection(1,root->siz-2,u,v);
	return u->best;
}
void Debug(Node *u)
{
	if(u==null)return;
	PushDown(u);
	Debug(u->ch[0]);
	if(u->val!=-INF)
		printf("%d ",u->val);
	Debug(u->ch[1]);
	//PushUp(u);
}

int c[MAXN];

int main()
{
	int N,M;
	char op[20];
	Init();
	Read(N);Read(M);
	for(int i=1;i<=N;i++)
		Read(c[i]);
	c[0]=0;c[N+1]=0;
	root=MakeTree(c,0,N+1);
	for(int i=1,p,t,d;i<=M;i++)
	{
		//printf("(**)----debug%d----\n",i);
		//Debug(root);
		//printf("\n(%2d)----debug%d----\n",root->best,i);
		scanf("%s",op);
		switch(op[0])
		{
			case 'I':
				Read(p);Read(t);
				for(int j=1;j<=t;j++)
					Read(c[j]);
				Insert(c,1,t,p);
				break;
			case 'D':
				Read(p);Read(t);
				Delete(p,p+t-1);
				break;
			case 'M':
				if(op[2]=='K')
				{
					Read(p);Read(t);Read(d);
					MakeSame(p,p+t-1,d);
				}
				else
					printf("%d\n",MaxSum());
				break;
			case 'R':
				Read(p);Read(t);
				Reverse(p,p+t-1);
				break;
			case 'G':
				Read(p);Read(t);
				printf("%d\n",GetSum(p,p+t-1));
				break;
		}
	}
	return 0;
}
