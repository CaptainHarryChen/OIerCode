#include<cstdio>
#include<cstring>
#include<cstdlib>
const int MAXN=200005,MAXM=100005;
struct Node
{
	int num,pri,size;
	Node *son[2];
	Node(){}
	Node(int n)
	{son[0]=son[1]=NULL;num=n;pri=rand();size=1;}
	void Update()
	{
		size=1;
		if(son[0])size+=son[0]->size;
		if(son[1])size+=son[1]->size;
	}
};
class Treap
{
	Node *root;
	Node *newNode(int val)
	{
		*cur=Node(val);
		return cur++;
	}
	int cmp(int a,int b)
	{
		if(a==b)return -1;
		return a>b;
	}
	void Rotate(Node *&x,bool d)
	{
		Node *y=x->son[d];
		x->son[d]=y->son[d^1];
		y->son[d^1]=x;
		x->Update();
		y->Update();
		x=y;
	}
	void Insert(int val,Node *&x)
	{
		if(x==NULL)
		{
			x=newNode(val);
			return;
		}
		int k=cmp(val,x->num);
		Insert(val,x->son[k]);
		if(x->son[k]->pri<x->pri)
			Rotate(x,k);
		x->Update();
	}
public:
	static Node _new[MAXN*20],*cur;
	Treap(){root=NULL;}
	void Insert(int val){Insert(val,root);}
	long long BiggerNum(int val)
	{
		Node *x=root;
		int k;
		long long ret=0;
		while(x)
		{
			k=cmp(val,x->num);
			if(k==0)
			{
				ret++;
				if(x->son[1])
					ret+=x->son[1]->size;
			}
			if(k==-1)
				break;
			x=x->son[k];
		}
		if(x&&x->son[1])
			ret+=x->son[1]->size;
		return ret;
	}
	long long SmallerNum(int val)
	{
		Node *x=root;
		int k;
		long long ret=0;
		while(x)
		{
			k=cmp(val,x->num);
			if(k==1)
			{
				ret++;
				if(x->son[0])
					ret+=x->son[0]->size;
			}
			if(k==-1)
				break;
			x=x->son[k];
		}
		if(x&&x->son[0])
			ret+=x->son[0]->size;
		return ret;
	}
};
class SegmentTree
{
	Treap node[MAXN*4];
public:
	static int N;
	void clear()
	{
		memset(node,0,sizeof node);
	}
	void Insert(int pos,int val,int id=1,int l=1,int r=N)
	{
		if(r<pos||pos<l)
			return;
		node[id].Insert(val);
		if(l==r)
			return;
		Insert(pos,val,id*2,l,(l+r)/2);
		Insert(pos,val,id*2+1,(l+r)/2+1,r);
	}
	long long BiggerNum(int L,int R,int val,int id=1,int l=1,int r=N)
	{
		if(r<L||R<l)
			return 0;
		if(L<=l&&r<=R)
			return node[id].BiggerNum(val);
		long long ret=0;
		ret+=BiggerNum(L,R,val,id*2,l,(l+r)/2);
		ret+=BiggerNum(L,R,val,id*2+1,(l+r)/2+1,r);
		return ret;
	}
	long long SmallerNum(int L,int R,int val,int id=1,int l=1,int r=N)
	{
		if(r<L||R<l)
			return 0;
		if(L<=l&&r<=R)
			return node[id].SmallerNum(val);
		long long ret=0;
		ret+=SmallerNum(L,R,val,id*2,l,(l+r)/2);
		ret+=SmallerNum(L,R,val,id*2+1,(l+r)/2+1,r);
		return ret;
	}
};
class BIT
{
	int sum[MAXN];
public:
	void clear()
	{
		memset(sum,0,sizeof sum);
	}
	void add(int pos,int val)
	{
		if(pos==0)
			return;
		while(pos<MAXN)
		{
			sum[pos]+=val;
			pos+=pos&(-pos);
		}
	}
	int get(int pos)
	{
		if(pos==0)
			return 0;
		int ret=0;
		while(pos>0)
		{
			ret+=sum[pos];
			pos-=pos&(-pos);
		}
		return ret;
	}
};
int SegmentTree::N;
Node Treap::_new[MAXN*20],*Treap::cur;
int num[MAXN],del[MAXM],pos[MAXN];
long long ans[MAXM];
bool delted[MAXN];
BIT cnt1;
SegmentTree cnt2;
int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		cnt1.clear();
		cnt2.clear();
		memset(delted,0,sizeof delted);
		Treap::cur=Treap::_new;
		SegmentTree::N=n;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",num+i);
			pos[num[i]]=i;
		}
		for(int i=1;i<=m;i++)
		{
			scanf("%d",del+i);
			delted[del[i]]=1;
		}
		long long sum=0,cnt=0;
		for(int i=1;i<=n;i++)
		{
			if(delted[num[i]])
				continue;
			cnt++;
			cnt1.add(num[i],1);
			cnt2.Insert(i,num[i]);
			sum+=cnt-cnt1.get(num[i]);
		}
		for(int i=m;i>=1;i--)
		{
			cnt2.Insert(pos[del[i]],del[i]);
			if(pos[del[i]]>1)
				sum+=cnt2.BiggerNum(1,pos[del[i]]-1,del[i]);
			if(pos[del[i]]<n)
				sum+=cnt2.SmallerNum(pos[del[i]]+1,n,del[i]);
			ans[i]=sum;
		}
		for(int i=1;i<=m;i++)
			printf("%lld\n",ans[i]);
	}
	return 0;
}
