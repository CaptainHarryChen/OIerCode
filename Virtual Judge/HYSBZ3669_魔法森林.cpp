#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=50005,MAXM=100005;

namespace LCT {
	
	struct Node *null;
	struct Node {
		int val,id,siz,maxval,maxid;
		bool rev;
		Node *fa,*ch[2];
		Node(){};
		Node(int i,int v) {
			fa=ch[0]=ch[1]=null;
			val=maxval=v;
			id=maxid=i;
			rev=false;
			siz=1;
		}
		bool IsRoot() {
			return fa==null||(fa->ch[0]!=this&&fa->ch[1]!=this);
		}
		int Dir() {
			return fa->ch[1]==this;
		}
		void SetChild(Node *c,int d) {
			ch[d]=c;
			if(c!=null)
				c->fa=this;
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
		void PushUp() {
			siz=ch[0]->siz+ch[1]->siz+1;
			maxval=val;
			maxid=id;
			if(maxval<ch[0]->maxval)
				maxval=ch[0]->maxval,maxid=ch[0]->maxid;
			if(maxval<ch[1]->maxval)
				maxval=ch[1]->maxval,maxid=ch[1]->maxid;
		}
	};

	Node node[MAXN+MAXM],*end;
	
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
		u->PushUp();
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
	}
	void Access(Node *u) {
		Node *last=null,*s=u;
		while(u!=null)
		{
			Splay(u);
			u->PushDown();
			u->SetChild(last,1);
			u->PushUp();
			last=u;
			u=u->fa;
		}
		Splay(s);
	}
	void MakeRoot(Node *u) {
		Access(u);
		u->rev^=1;
	}
		
	Node *FindRoot(Node *u) {
		Access(u);
		for(u->PushDown();u->ch[0]!=null;u=u->ch[0],u->PushDown());
		return u;
	}

	void Init() {
		end=node+1;
		null=node;
		null->fa=null->ch[0]=null->ch[1]=null;
		null->id=null->maxid=null->val=null->maxval=0;
		null->siz=0;
		null->rev=false;
	}
	Node *NewNode(int id,int val) {
		*end=Node(id,val);
		return end++;
	}
	bool IsConnected(Node *u,Node *v) {
		return FindRoot(u)==FindRoot(v);
	}
	void Link(Node *u,Node *v) {
		MakeRoot(u);
		u->fa=v;
	}
	void Cut(Node *u,Node *v) {
		MakeRoot(u);
		Access(v);
		v->PushDown();
		v->SetChild(null,0);
		v->PushUp();
		u->fa=null;
	}
	int GetPathMaxi(Node *u,Node *v) {
		MakeRoot(u);
		Access(v);
		return v->maxid;
	}
}

struct Edge {
	int u,v,a,b;
	bool operator < (const Edge &t)const {
		return a<t.a;
	}
}E[MAXM];

LCT::Node *ver[MAXN],*edge[MAXM];
int N,M;

void AddEdge(int i) {
	Edge ei=E[i];
	if(ei.u==ei.v)
		return;
	if(!LCT::IsConnected(ver[ei.u],ver[ei.v])) {
		LCT::Link(ver[ei.u],edge[i]);
		LCT::Link(ver[ei.v],edge[i]);
		return;
	}
	int j=LCT::GetPathMaxi(ver[ei.u],ver[ei.v]);
	Edge ej=E[j];
	if(ej.b>ei.b) {
		LCT::Cut(ver[ej.u],edge[j]);
		LCT::Cut(ver[ej.v],edge[j]);
		LCT::Link(ver[ei.u],edge[i]);
		LCT::Link(ver[ei.v],edge[i]);
		return;
	}
}

int main() {
	
	LCT::Init();
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
		ver[i]=LCT::NewNode(i,0);
	for(int i=1;i<=M;i++)
		scanf("%d%d%d%d",&E[i].u,&E[i].v,&E[i].a,&E[i].b);
	sort(E+1,E+M+1);
	for(int i=1;i<=M;i++)
		edge[i]=LCT::NewNode(i,E[i].b);
	int ans=0x7FFFFFFF;
	for(int i=1;i<=M;i++) {
		AddEdge(i);
		if(LCT::IsConnected(ver[1],ver[N]))
			ans=min(ans,E[i].a+E[LCT::GetPathMaxi(ver[1],ver[N])].b);
	}
	if(ans==0x7FFFFFFF)
		puts("-1");
	else
		printf("%d\n",ans);
	return 0;
}
