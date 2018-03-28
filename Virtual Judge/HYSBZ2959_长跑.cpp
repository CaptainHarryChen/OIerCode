#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=150005;

namespace LCT {
	struct Node *null;
	struct Node {
		int val,sum,id;
		Node *ch[2],*fa;
		bool rev;
		Node(){}
		Node(int v,int i) {
			val=sum=v;
			id=i;
			ch[0]=ch[1]=fa=null;
			rev=false;
		}
		bool IsRoot() {
			return fa==null||(fa->ch[0]!=this&&fa->ch[1]!=this);
		}
		void SetChild(Node *c,int d) {
			ch[d]=c;
			if(c!=null)
				c->fa=this;
		}
		int Dir() {
			return fa->ch[1]==this;
		}
		void PushUp() {
			sum=ch[0]->sum+val+ch[1]->sum;
		}
		void PushDown() {
			if(rev) {
				swap(ch[0],ch[1]);
				if(ch[0]!=null)
					ch[0]->rev^=1;
				if(ch[1]!=null)
					ch[1]->rev^=1;
				rev=false;
			}
		}
	};
}

namespace DSU {
	using LCT::Node;
	Node *fa[MAXN];
	Node *temp;
	Node *FindRoot(Node *x) {
		if(fa[x->id]==x)
			return x;
		return fa[x->id]=FindRoot(fa[x->id]);
	}
	void Union(Node *x,Node *y) {
		fa[y->id]=x;
	}
}

namespace LCT {
	Node node[MAXN],*end;
	void Init() {
		null=node;
		end=node+1;
		DSU::fa[0]=null;
		*null=Node(0,0);
	}
	Node *NewNode(int v,int i) {
		*end=Node(v,i);
		DSU::fa[i]=end;
		return end++;
	}
	void Rotate(Node *u) {
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
	}
	void Splay(Node *u) {
		while(!u->IsRoot()) {
			Node *v=u->fa;
			if(v->IsRoot()) {
				Rotate(u);
				break;
			}
			v->fa->PushDown();
			v->PushDown();
			if(u->Dir()==v->Dir())
				Rotate(v);
			else
				Rotate(u);
			Rotate(u);
		}
		u->PushUp();
	}
	void Access(Node *u) {
		Node *last=null;
		while(u!=null)
		{
			Splay(u);
			u->PushDown();
			u->SetChild(last,1);
			u->PushUp();
			last=u;
			u=DSU::FindRoot(u->fa);
		}
	}
	Node *FindRoot(Node *u) {
		Access(u);Splay(u);
		for(u->PushDown();u->ch[0]!=null;u=u->ch[0],u->PushDown());
		return u;
	}
	bool IsConnected(Node *u,Node *v) {
		return FindRoot(u)==FindRoot(v);
	}
	void MakeRoot(Node *u) {
		Access(u);Splay(u);
		u->rev^=1;
	}
	int GetPathSum(Node *u,Node *v) {
		MakeRoot(u);
		Access(v);Splay(v);
		return v->sum;
	}
	void Link(Node *u,Node *v) {
		MakeRoot(v);
		v->fa=u;
	}
	void Add(Node *u,int nval) {
		Access(u);Splay(u);
		u->val+=nval;
		u->PushUp();
	}
}

LCT::Node *id[MAXN];
int val[MAXN];

void Dfs(LCT::Node *u,LCT::Node *root) {
	DSU::Union(root,u);
	if(u->ch[0]!=LCT::null)
		Dfs(u->ch[0],root);
	if(u->ch[1]!=LCT::null)
		Dfs(u->ch[1],root);
}

void AddEdge(LCT::Node *u,LCT::Node *v) {
	if(!LCT::IsConnected(u,v)) {
		LCT::Link(u,v);
		return;
	}
	LCT::MakeRoot(u);
	LCT::Access(v);
	LCT::Splay(u);
	Dfs(u,u);
	u->val=u->sum;
	u->ch[0]=u->ch[1]=LCT::null;
}

int main() {
	LCT::Init();
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) {
		scanf("%d",&val[i]);
		id[i]=LCT::NewNode(val[i],i);
	}
	int p,a,b;
	for(int i=1;i<=m;i++) {
		scanf("%d%d%d",&p,&a,&b);
		if(p==1)
			AddEdge(DSU::FindRoot(id[a]),DSU::FindRoot(id[b]));
		else if(p==2) {
			LCT::Add(DSU::FindRoot(id[a]),b-val[a]);
			val[a]=b;
		}
		else {
			if(!LCT::IsConnected(DSU::FindRoot(id[a]),DSU::FindRoot(id[b])))
				puts("-1");
			else
				printf("%d\n",LCT::GetPathSum(DSU::FindRoot(id[a]),DSU::FindRoot(id[b])));
		}
	}
	return 0;
}
