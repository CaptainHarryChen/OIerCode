#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define MAXN 100005
struct Node
{
	int val,pri,sz;
	Node *son[2];
	Node(){}
	Node(int v){val=v;pri=rand();sz=1;son[0]=son[1]=NULL;}
	void Update()
	{
		sz=1;
		if(son[0])sz+=son[0]->sz;
		if(son[1])sz+=son[1]->sz;
	}
}nodes[MAXN],*cur=nodes;
struct Treap
{
	Node *root;
	Treap(){root=NULL;}
	int cmp(int x,int y){return x==y?-1:x>y;}
	int size(){return root?root->sz:0;}
	Node *newNode(int val)
	{
		*cur=Node(val);
		return cur++;
	}
	void Rotate(Node *&x,int d)
	{
		Node *y=x->son[!d];
		x->son[!d]=y->son[d];
		y->son[d]=x;
		x->Update();
		y->Update();
		x=y;
	}
	void Insert(Node *&now,Node *x)
	{
		if(now==NULL)
			now=x;
		else
		{
			int d=cmp(x->val,now->val);
			Insert(now->son[d],x);
			if(now->son[d]->pri<now->pri)
				Rotate(now,!d);
			now->Update();
		}
	}
	void Insert(Node *x)
	{x->son[0]=x->son[1]=NULL;x->Update();Insert(root,x);}
	Node *FindKth(int k)
	{
		Node *now=root;
		if(!root)return NULL;
		int rank=(now->son[0]?now->son[0]->sz:0)+1;
		while(now)
		{
			if(rank==k)
				return now;
			else if(rank>k)
			{
				now=now->son[0];
				if(!now)break;
				rank-=(now->son[1]?now->son[1]->sz:0)+1;
			}
			else
			{
				now=now->son[1];
				if(!now)break;
				rank+=(now->son[0]?now->son[0]->sz:0)+1;
			}
		}
		return NULL;
	}
	void Merge(Treap &out,Node *now)
	{
		if(now==NULL)return;
		Merge(out,now->son[0]);
		Merge(out,now->son[1]);
		out.Insert(now);
	}
	void Merge(Treap &out)
	{Merge(out,root);root=NULL;}
}T[MAXN];
int S[MAXN];
int Root(int x){return S[x]==x?x:S[x]=Root(S[x]);}
void Merge(int a,int b)
{
	int x=Root(a),y=Root(b);
	if(a==b)return;
	if(T[x].size()<T[y].size())swap(x,y);
	S[y]=x;
	T[y].Merge(T[x]);
}
int main()
{
	int a,b,n,m,Q;
	char op[3];
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		nodes[i]=Node(x);
		T[i].Insert(nodes+i);
	}
	for(int i=1;i<=n;i++)S[i]=i;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		Merge(a,b);
	}
	scanf("%d",&Q);
	for(int q=1;q<=Q;q++)
	{
		scanf("%s%d%d",op,&a,&b);
		if(op[0]=='Q')
		{
			Node *ans=T[Root(a)].FindKth(b);
			if(!ans)printf("-1\n");
			else printf("%d\n",ans-nodes);
		}
		else
			Merge(a,b);
	}
	return 0;
}
