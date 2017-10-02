#include<cstdio>
#include<queue>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXM=300005;
int n,m;
struct Node
{
	int osiz,siz,type;
	int val,mx;
	Node *pa,*son[2];
	bool prefer,flip;
	Node()
	{osiz=siz=type=0;pa=son[0]=son[1]=NULL;val=mx=0;prefer=flip=false;}
	Node(int _type,int _val)
	{
		osiz=0;
		type=siz=_type;
		pa=son[0]=son[1]=NULL;
		val=mx=_val;
		prefer=flip=false;
	}
	void Update()
	{
		siz=type;mx=val;
		if(son[0])
		{siz+=son[0]->siz;mx=max(mx,son[0]->mx);}
		if(son[1])
		{siz+=son[1]->siz;mx=max(mx,son[1]->mx);}
		siz+=osiz;
	}
	void Flip()
	{
		if(!flip)return;
		swap(son[0],son[1]);
		if(son[0])son[0]->flip^=1;
		if(son[1])son[1]->flip^=1;
		flip=false;
	}
};
class LCT
{
public:
	int nodescnt;
	void NewNode(int _type,int val)
	{
		nodes[++nodescnt]=Node(_type,val);
	}
	void Rotate(Node *x)
	{
		Node *y=x->pa;
		int d=(y->son[1]==x);
		x->pa=y->pa;
		x->prefer=y->prefer;
		if(y->pa&&y->prefer)
			y->pa->son[y->pa->son[1]==y]=x;
		y->son[d]=x->son[!d];
		if(x->son[!d])
		{
			x->son[!d]->pa=y;
			x->son[!d]->prefer=true;
		}
		x->son[!d]=y;
		y->pa=x;
		y->prefer=true;
		y->Update();
		x->Update();
	}
	void Splay(Node *x)
	{
		Node *y,*z;
		while(x->pa&&x->prefer)
		{
			y=x->pa;
			z=y->pa;
			if(z)z->Flip();
			y->Flip();
			x->Flip();
			if(z==NULL||y->prefer==false)
			{
				Rotate(x);
				break;
			}
			else
			{
				z->Flip();
				if((z->son[1]==y)==(y->son[1]==x))
				{
					Rotate(y);
					Rotate(x);
				}
				else
				{
					Rotate(x);
					Rotate(x);
				}
			}
		}
		x->Flip();
		x->Update();
	}
	LCT()
	{nodescnt=0;}
	void Access(Node *x)
	{
		Node *last=NULL;
		while(x)
		{
			Splay(x);
			if(x->son[1])
			{
				x->son[1]->prefer=false;
				x->osiz+=x->son[1]->siz;
			}
			x->son[1]=last;
			if(last)
			{
				last->prefer=true;
				x->osiz-=last->siz;
				if(x->osiz<0)
					puts("ERROR");
			}
			x->Update();
			last=x;
			x=x->pa;
		}
	}
	void MakeRoot(Node *x)
	{
		Access(x);
		Splay(x);
		x->flip^=1;
	}
	void Link(Node *x,Node *y)
	{
		MakeRoot(x);
		Splay(x);
		Access(y);
		Splay(y);
		x->pa=y;
		y->osiz+=x->siz;
		y->Update();
	}
	void Cut(Node *x,Node *y)
	{
		MakeRoot(x);
		Access(y);
		Splay(x);
		if(x->son[1]!=y)
		{
			puts("ERROR");
			return;
		}
		x->son[1]->pa=NULL;
		x->son[1]->prefer=false;
		x->son[1]=NULL;
		x->Update();
	}
	Node nodes[MAXN+MAXM];
};
class UFset
{
	int S[MAXN];
public:
	int Find(int x)
	{
		if(S[x]==0)
			return x;
		return S[x]=Find(S[x]);
	}
	void Union(int a,int b)
	{
		int r1=Find(a),r2=Find(b);
		if(r1!=r2)
			S[r1]=r2;
	}
};
struct Edge
{
	int u,v,val,id;
	bool vis;
	Edge(){}
	Edge(int _u,int _v,int _val):u(_u),v(_v),val(_val){}
	bool operator < (const Edge &t)const
	{return val<t.val;}
};
LCT T;
UFset U;
priority_queue<Edge> Q;
Edge edge[MAXM];
bool deleted[MAXM];
int rest;
void Connect(int id)
{
	Edge &t=edge[id];
	Node *x=T.nodes+t.u;
	Node *y=T.nodes+t.v;
	int r1=U.Find(t.u);
	int r2=U.Find(t.v);
	if(r1!=r2)
	{
		T.Access(x);
		T.Splay(x);
		T.Access(y);
		T.Splay(y);
		if(x->siz%2==1&&y->siz%2==1)
			rest-=2;
		T.Link(x,T.nodes+id+n);
		T.Link(y,T.nodes+id+n);
		U.Union(r1,r2);
		Q.push(t);
	}
	else
	{
		T.MakeRoot(x);
		T.Access(y);
		T.Splay(x);
		int mxe=x->mx;
		if(mxe<=t.val)
			return;
		Node *temp=x;
		while(1)
		{
			if(temp->val==mxe)
				break;
			if(temp->son[0]&&temp->son[0]->mx==mxe)
				temp=temp->son[0];
			else if(temp->son[1]&&temp->son[1]->mx==mxe)
				temp=temp->son[1];
			else
			{
				puts("ERROR!\n");
				exit(0);
			}
		}
		T.Cut(T.nodes+edge[temp-T.nodes-n].u,temp);
		T.Cut(T.nodes+edge[temp-T.nodes-n].v,temp);
		deleted[temp-T.nodes-n]=true;
		T.Link(x,T.nodes+n+id);
		T.Link(y,T.nodes+n+id);
		U.Union(t.u,t.v);
		Q.push(edge[id]);
	}
}
void solve()
{
	bool flag=true;
	Edge temp;
	Node *x;
	while(!Q.empty()&&flag)
	{
		flag=false;
		temp=Q.top();
		if(deleted[temp.id])
		{
			Q.pop();
			flag=true;
		}
		else
		{
			x=T.nodes+temp.u;
			T.Cut(x,T.nodes+n+temp.id);
			T.MakeRoot(x);
			if(x->siz%2==0)
			{
				Q.pop();
				flag=true;
			}
			T.Link(x,T.nodes+n+temp.id);
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	if(n%2==1)
	{
		for(int i=1;i<=m;i++)
			puts("-1");
		return 0;
	}
	for(int i=1;i<=n;i++)
		T.NewNode(1,0);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].val);
		edge[i].id=i;
		T.NewNode(0,edge[i].val);
	}
	rest=n;
	int it;
	for(it=1;it<=m;it++)
	{
		Connect(it);
		if(rest==0)
		{
			solve();
			printf("%d\n",Q.top().val);
			break;
		}
		printf("-1\n");
	}
	if(rest)
		return 0;
	for(it++;it<=m;it++)
	{
		Connect(it);
		solve();
		printf("%d\n",Q.top().val);
	}
	return 0;
}
