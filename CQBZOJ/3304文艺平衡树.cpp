#include<cstdio>
#include<algorithm>
const int MAXN=100005;
struct Node
{
	int val,size,cnt;
	bool rev;
	Node *son[2],*fa;
	void Update()
	{
		size=cnt+son[0]->size+son[1]->size;
	}
}nodes[MAXN],*cur=nodes+1,*null=nodes;
Node *new_Node(int val)
{
	cur->val=val;
	cur->size=cur->cnt=1;
	cur->rev=0;
	cur->son[0]=cur->son[1]=cur->fa=null;
	return cur++;
}
struct SplayTree
{
	Node *root;
	SplayTree(){root=null;}
	int cmp(int a,int b){return a==b?-1:a>b;}
	void Rev(Node *u)
	{
		if(u->rev)
		{
			std::swap(u->son[0],u->son[1]);
			if(u->son[0]!=null)u->son[0]->rev^=1;
			if(u->son[1]!=null)u->son[1]->rev^=1;
			u->rev=0;
		}
	}
	void Rotate(Node *x)
	{
		Node *y=x->fa;
		Rev(y);Rev(x);
		int d=y->son[0]==x;
		x->fa=y->fa;
		if(y->fa!=null)y->fa->son[y->fa->son[1]==y]=x;
		y->son[!d]=x->son[d];
		if(x->son[d]!=null)x->son[d]->fa=y;
		x->son[d]=y;
		y->fa=x;
		if(root==y)root=x;
		x->Update();
		y->Update();
	}
	void Splay(Node *x,Node *r)
	{
		while(x->fa!=r)
		{
			Node *y=x->fa;
			if(y->fa==r)
			{
				Rotate(x);
				break;
			}
			else
			{
				Node *z=y->fa;
				if((z->son[1]==y)==(y->son[1]==x))
					Rotate(y),Rotate(x);
				else
					Rotate(x),Rotate(x);
			}
		}
		x->Update();
	}
	Node *Get_pre_next(Node *x,int f)
	{
		if(x->son[f]==null)return null;
		x=x->son[f];
		while(x->son[!f]!=null)x=x->son[!f];
		return x;
	}
	void Insert(int val)
	{
		if(root==null)
		{root=new_Node(val);return;}
		Node *u=root;
		while(1)
		{
			int d=cmp(val,u->val);
			if(d==-1)
			{
				u->cnt++;
				Splay(u,null);
				break;
			}
			if(u->son[d]==null)
			{
				u->son[d]=new_Node(val);
				u->son[d]->fa=u;
				Splay(u->son[d],null);
				break;
			}
			u=u->son[d];
		}
	}
	Node *find_rank(int rank)
	{
		Node *u=root;
		Rev(u);
		int tmp=u->son[0]->size+1;
		while(1)
		{
			if(rank>=tmp&&rank<tmp+u->cnt)
			{
				Splay(u,null);
				return u;
			}
			if(rank<tmp)
			{
				Rev(u->son[0]);
				tmp=tmp-u->son[0]->cnt-u->son[0]->son[1]->size;
				u=u->son[0];
			}
			else
			{
				Rev(u->son[1]);
				tmp=tmp+u->cnt+u->son[1]->son[0]->size;
				u=u->son[1];
			}
		}
		return null;
	}
	void Flip(int l,int r)
	{
		Node *pre=find_rank(l-1);
		Node *nxt=find_rank(r+1);
		Splay(pre,null);
		Splay(nxt,pre);
		root->son[1]->son[0]->rev^=1;
	}
}T;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	T.Insert(0);
	for(int i=1;i<=n;i++)
		T.Insert(i);
	T.Insert(n+1);
	int l,r;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&l,&r);
		T.Flip(l+1,r+1);
	}
	for(int i=1;i<n;i++)
		printf("%d ",T.find_rank(i+1)->val);
	printf("%d",T.find_rank(n+1)->val);
	return 0;
}
