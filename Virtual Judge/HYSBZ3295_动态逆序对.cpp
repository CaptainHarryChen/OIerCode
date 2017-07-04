#include<cstdio>
#include<cstdlib>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?b:a)
#define MAXN 100005
#define SEG_NODES 400005
#define TRE_NODES 4000005
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
	int x,size,pri;
	Node *son[2];
	Node(){son[0]=son[1]=0;size=pri=0;pri=rand();}
	Node(int x):x(x){size=1;son[0]=son[1]=0;pri=rand();}
	void Update()
	{
		size=1;
		size+=son[0]->size;
		size+=son[1]->size;
	}
};
Node _new[TRE_NODES],*cur=_new,*null=new Node;
struct Treap
{
	Node *root;
	Treap(){root=null;}
	Node *newNode(int x)
	{
		*cur=Node(x);
		cur->son[0]=cur->son[1]=null;
		cur++;
		return cur-1;
	}
	int cmp(int x,int y)
	{return x==y?-1:x>y;}
	void Rotate(Node *&p,int d)
	{
		Node *y=p->son[!d];
		p->son[!d]=y->son[d];
		y->son[d]=p;
		p->Update();
		y->Update();
		p=y;
	}
	void Insert(Node *&p,int x)
	{
		if(p==null)
		{p=newNode(x);}
		else
		{
			int k=cmp(x,p->x);
			Insert(p->son[k],x);
			if(p->son[k]->pri<p->pri)
				Rotate(p,!k);
			else p->size++;
		}
	}
	int BiggerNum(int x)
	{
		Node *p=root;
		int ret=0;
		while(p!=null)
		{
			if(p->x>x)
			{
				ret+=p->son[1]->size+1;
				p=p->son[0];
			}
			else if(p->x<x)
				p=p->son[1];
		}
		return ret;
	}
	int SmallerNum(int x)
	{
		Node *p=root;
		int ret=0;
		while(p!=null)
		{
			if(p->x>x)
				p=p->son[0];
			else if(p->x<x)
			{
				ret+=p->son[0]->size+1;
				p=p->son[1];
			}
		}
		return ret;
	}
};
Treap T[SEG_NODES];
int num[MAXN],pos[MAXN],deln[MAXN];
long long ans[MAXN];
bool del[MAXN];
void Insert(int id,int L,int R,int x,int P)
{
	if(L>R||L>P||R<P)return;
	T[id].Insert(T[id].root,x);
	if(L==R)return;
	int mid=(L+R)>>1;
	Insert(id<<1,L,mid,x,P);
	Insert((id<<1)+1,mid+1,R,x,P);
}
long long BiggerNum(int id,int L,int R,int x,int l,int r)
{
	if(L>R||l>R||r<L)return 0;
	if(l>=L&&r<=R)
		return T[id].BiggerNum(x);
	long long ret=0;
	int mid=(l+r)>>1;
	ret+=BiggerNum(id<<1,L,R,x,l,mid);
	ret+=BiggerNum((id<<1)+1,L,R,x,mid+1,r);
	return ret;
}
long long SmallerNum(int id,int L,int R,int x,int l,int r)
{
	if(L>R||l>R||r<L)return 0;
	if(l>=L&&r<=R)
		return T[id].SmallerNum(x);
	long long ret=0;
	int mid=(l+r)>>1;
	ret+=SmallerNum(id<<1,L,R,x,l,mid);
	ret+=SmallerNum((id<<1)+1,L,R,x,mid+1,r);
	return ret;
}
int bit[MAXN];
void Modify(int x)
{
	for(;x<MAXN;x+=(x&(-x)))
		bit[x]++;
}
long long GetSum(int x)
{
	long long ret=0;
	for(;x>0;x-=(x&(-x)))
		ret+=bit[x];
	return ret;
}
int main()
{
	int n,m;
	long long sum=0;
	Read(n);Read(m);
	for(int i=1;i<=n;i++)
	{
		Read(num[i]);
		pos[num[i]]=i;
	}
	for(int i=1;i<=m;i++)
	{
		Read(deln[i]);
		del[deln[i]]=1;
	}
	for(int i=1,cnt=0;i<=n;i++)
	{
		if(del[num[i]])continue;
		cnt++;
		Insert(1,1,n,num[i],i);
		Modify(num[i]);
		sum+=cnt-GetSum(num[i]);
	}
	for(int i=m;i>0;i--)
	{
		Insert(1,1,n,deln[i],pos[deln[i]]);
		sum+=BiggerNum(1,1,pos[deln[i]]-1,deln[i],1,n)+SmallerNum(1,pos[deln[i]]+1,n,deln[i],1,n);
		ans[i]=sum;
	}
	for(int i=1;i<=m;i++)
		printf("%I64d\n",ans[i]);
	return 0;
}
