#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXM=1000005,MAXQ=MAXN;

template<class T> inline void Input(T &x)
{
	char c;
	while(c=getchar(),c!=EOF)
	{
		if('0'<=c&&c<='9')
		{
			for(x=0;'0'<=c&&c<='9';c=getchar())
				x=x*10+c-'0';
			return;
		}
	}
}

struct Node *null;
struct Node
{
	int val,maxi,maxi_id,siz,edge_id;
	bool rev;
	Node *fa,*ch[2];
	Node()
	{
		fa=ch[0]=ch[1]=null;
		val=maxi=maxi_id=edge_id=0;
		siz=1;
		rev=false;
	}
	Node(int a,int ei)
	{
		fa=ch[0]=ch[1]=null;
		val=maxi=a;
		maxi_id=edge_id=ei;
		siz=1;
		rev=false;
	}
	inline bool IsRoot()
	{return fa==null||(fa->ch[0]!=this&&fa->ch[1]!=this);}
	inline int Dir()
	{return fa->ch[1]==this;}
	inline void SetChild(Node *c,int d)
	{
		ch[d]=c;
		if(c!=null)
			c->fa=this;
	}
	inline void PushUp()
	{
		siz=ch[0]->siz+ch[1]->siz+1;
		maxi_id=edge_id;
		maxi=val;
		if(maxi<ch[0]->maxi)
			maxi=ch[0]->maxi,maxi_id=ch[0]->maxi_id;
		if(maxi<ch[1]->maxi)
			maxi=ch[1]->maxi,maxi_id=ch[1]->maxi_id;
	}
	inline void PushDown()
	{
		if(rev)
		{
			swap(ch[0],ch[1]);
			if(ch[0])ch[0]->rev^=1;
			if(ch[1])ch[1]->rev^=1;
			rev=false;
		}
	}
}node[MAXN+MAXM];

inline void Init()
{
	null=node;
	null->fa=null->ch[0]=null->ch[1]=null;
	null->siz=0;
}
inline void Rotate(Node *u)
{
	Node *v=u->fa;
	v->PushDown();
	u->PushDown();
	int d=u->Dir();
	if(!v->IsRoot())
		v->fa->SetChild(u,v->Dir());
	else
		u->fa=v->fa;
	v->SetChild(u->ch[d^1],d);
	u->SetChild(v,d^1);
	v->PushUp();
	u->PushUp();
}
inline void Splay(Node *u)
{
	while(!u->IsRoot())
	{
		Node *v=u->fa;
		Node *w=v->fa;
		if(v->IsRoot())
		{
			Rotate(u);
			break;
		}
		w->PushDown();
		v->PushDown();
		if(u->Dir()==v->Dir())
			Rotate(v);
		else
			Rotate(u);
		Rotate(u);
	}
}
inline void Access(Node *u)
{
	Node *last=null;
	while(u!=null)
	{
		Splay(u);
		u->PushDown();
		u->SetChild(last,1);
		u->PushUp();
		last=u;
		u=u->fa;
	}
}
inline Node *FindRoot(Node *u)
{
	Access(u);
	Splay(u);
	u->PushDown();
	while(u->ch[0]!=null)
	{
		u->PushDown();
		u=u->ch[0];
	}
	return u;
}
inline bool IsConnected(Node *u,Node *v)
{
	return FindRoot(u)==FindRoot(v);
}
inline void MakeRoot(Node *u)
{
	Access(u);
	Splay(u);
	u->rev^=1;
}
inline void Link(Node *u,Node *v)
{
	MakeRoot(u);
	u->fa=v;
}
inline void Cut(Node *u,Node *v)
{
	MakeRoot(u);
	Access(v);
	Splay(v);
	v->SetChild(null,0);
	v->PushUp();
	u->fa=null;
}
inline int FindMaxi(Node *u,Node *v)
{
	MakeRoot(u);
	Access(v);
	Splay(u);
	return u->maxi_id;
}

struct Edge
{
	int u,v,t;
	Edge(){}
	Edge(int _u,int _v){u=_u;v=_v;t=-1;}
	bool operator < (const Edge &y)const
	{
		if(u<y.u)
			return true;
		if(u>y.u)
			return false;
		return v<y.v||(v==y.v&&t<y.t);
	}
};

int N,M,Q;
Node *id[MAXN+MAXM];
Edge pipe[MAXM];
bool broken[MAXM];
int ans[MAXQ],op[MAXQ][3];

inline void add_edge(int i)
{
	Edge &a=pipe[i];
	if(!IsConnected(id[a.u],id[a.v]))
	{
		Link(id[a.u],id[N+i]);
		Link(id[a.v],id[N+i]);
		return;
	}
	int j=FindMaxi(id[a.u],id[a.v]);
	Edge &b=pipe[j];
	if(b.t>a.t)
	{
		Cut(id[b.u],id[N+j]);
		Cut(id[b.v],id[N+j]);
		Link(id[a.u],id[N+i]);
		Link(id[a.v],id[N+i]);
		return;
	}
}

int main()
{
	Init();
	Input(N);Input(M);Input(Q);
	for(register int i=1;i<=M;i++)
	{
		Input(pipe[i].u);Input(pipe[i].v);Input(pipe[i].t);
		if(pipe[i].u>pipe[i].v)
			swap(pipe[i].u,pipe[i].v);
	}
	sort(pipe+1,pipe+M+1);
	for(register int i=1;i<=N;i++)
	{
		id[i]=node+i;
		*id[i]=Node(0,0);
	}
	for(register int i=1;i<=M;i++)
	{
		id[i+N]=node+i+N;
		*id[i+N]=Node(pipe[i].t,i);
	}
	for(register int i=1;i<=Q;i++)
	{
		Input(op[i][0]);Input(op[i][1]);Input(op[i][2]);
		if(op[i][0]==2)
		{
			if(op[i][1]>op[i][2])
				swap(op[i][1],op[i][2]);
			op[i][1]=lower_bound(pipe+1,pipe+M+1,Edge(op[i][1],op[i][2]))-pipe;
			broken[op[i][1]]=true;
		}
	}
	for(register int i=1;i<=M;i++)
		if(!broken[i])
			add_edge(i);
	for(register int i=Q;i>0;i--)
	{
		if(op[i][0]==1)
			ans[i]=pipe[FindMaxi(id[op[i][1]],id[op[i][2]])].t;
		else
			add_edge(op[i][1]);
	}
	for(register int i=1;i<=Q;i++)
		if(op[i][0]==1)
			printf("%d\n",ans[i]);
	
	return 0;
}
