#include<cstdio>
#include<map>
#include<algorithm>
const int MAXN=10005,MAXM=100005,MAXC=12;
struct LCT
{
	struct Node
	{
		int val,mx;
		Node *son[2],*fa;
		bool prefer,flip;
		void Flip()
		{
			if(!flip)return;
			std::swap(son[0],son[1]);
			if(son[0])son[0]->flip^=1;
			if(son[1])son[1]->flip^=1;
			flip=false;
		}
		void Update()
		{
			mx=val;
			if(son[0])mx=std::max(mx,son[0]->mx);
			if(son[1])mx=std::max(mx,son[1]->mx);
		}
	}nodes[MAXN];
	void Rotate(Node *x)
	{
		Node *y=x->fa;
		if(y==NULL)return;
		int d=y->son[0]==x;
		x->fa=y->fa;
		x->prefer=y->prefer;
		if(y->prefer&&y->fa)y->fa->son[y->fa->son[1]==y]=x;
		y->prefer=true;
		y->son[!d]=x->son[d];
		if(x->son[d])x->son[d]->fa=y;
		x->son[d]=y;
		y->fa=x;
		y->Update();
		x->Update();
	}
	void Splay(Node *x)
	{
		Node *y,*z;
		int d1,d2;
		while(x->prefer)
		{
			y=x->fa;
			z=y->fa;
			if(z)z->Flip();
			y->Flip();
			x->Flip();
			if(!y->prefer)
			{
				Rotate(x);
				break;
			}
			d1=y->son[1]==x;
			d2=z->son[1]==x;
			if(d1==d2)
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
		x->Flip();
		x->Update();
	}
	void Access(Node *x)
	{
		Node *last=NULL;
		while(x)
		{
			Splay(x);
			if(x->son[1])
				x->son[1]->prefer=false;
			x->son[1]=last;
			if(last)
				last->prefer=true;
			x->Update();
			last=x;
			x=x->fa;
		}
	}
	Node *FindRoot(Node *x)
	{
		Access(x);
		Splay(x);
		Node *u=x;
		while(u->son[0])
			u=u->son[0];
		Splay(u);
		return u;
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
		x->fa=y;
	}
	void Link(int x,int y){Link(nodes+x,nodes+y);}
	void Cut(Node *x)
	{
		Access(x);
		Splay(x);
		if(x->son[0])
		{
			x->son[0]->fa=NULL;
			x->son[0]->prefer=false;
		}
		x->son[0]=NULL;
	}
	void Cut(int x,int y)
	{
		MakeRoot(nodes+y);
		//debug();
		Cut(nodes+x);
	}
	void Modify(Node *x,int val)
	{
		x->val=val;
		x->mx=val;
		Access(x);
	}
	void Modify(int x,int val){Modify(nodes+x,val);}
	int FindPath(Node *u,Node *v)
	{
		MakeRoot(v);
		Access(u);
		Splay(u);
		return u->mx;
	}
	int FindPath(int u,int v){return FindPath(nodes+u,nodes+v);}
	bool BothIn(Node *u,Node *v)
	{
		Node *x=FindRoot(u);
		return x==FindRoot(v)&&x!=NULL;
	}
	bool BothIn(int u,int v){return BothIn(nodes+u,nodes+v);}
}T[MAXC];
int ecnt[MAXN][MAXC];
std::map<std::pair<int,int>,int>edge;
std::map<std::pair<int,int>,bool>haveEdge;
int main()
{
	int n,m,c,k;
	scanf("%d%d%d%d",&n,&m,&c,&k);
	for(int i=1,v;i<=n;i++)
	{
		scanf("%d",&v);
		for(int co=0;co<c;co++)
		{
			T[co].nodes[i].val=v;
			T[co].nodes[i].mx=v;
		}
	}
	for(int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		ecnt[u][w]++;
		ecnt[v][w]++;
		edge[std::make_pair(u,v)]=w;
		edge[std::make_pair(v,u)]=w;
		haveEdge[std::make_pair(u,v)]=1;
		haveEdge[std::make_pair(v,u)]=1;
		T[w].Link(u,v);
	}
	for(int i=1,op,u,v,w;i<=k;i++)
	{
		scanf("%d",&op);
		if(op==0)
		{
			scanf("%d%d",&u,&v);
			for(int co=0;co<c;co++)
				T[co].Modify(u,v);
		}
		else if(op==1)
		{
			scanf("%d%d%d",&u,&v,&w);
			int lco=-1;
			if(haveEdge[std::make_pair(u,v)]==0)
			{printf("No such edge.\n");continue;}
			lco=edge[std::make_pair(u,v)];
			if(lco==w)
			{printf("Success.\n");continue;}
			if(ecnt[u][w]>=2||ecnt[v][w]>=2)
			{printf("Error 1.\n");continue;}
			if(T[w].BothIn(u,v))
			{printf("Error 2.\n");continue;}
			T[lco].Cut(u,v);
			ecnt[u][lco]--;
			ecnt[v][lco]--;
			T[w].Link(u,v);
			ecnt[u][w]++;
			ecnt[v][w]++;
			edge[std::make_pair(u,v)]=w;
			edge[std::make_pair(v,u)]=w;
			printf("Success.\n");
		}
		else
		{
			scanf("%d%d%d",&w,&u,&v);
			if(!T[w].BothIn(u,v))
				printf("-1\n");
			else
				printf("%d\n",T[w].FindPath(u,v));
		}
	}
	return 0;
}
