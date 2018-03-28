#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005,MAXLOG=20;

namespace LCT {
	
	struct Node *null;
	struct Node {
		int id,siz,minid;
		bool rev;
		Node *fa,*ch[2];
		Node(){};
		Node(int i) {
			fa=ch[0]=ch[1]=null;
			id=minid=i;
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
			minid=min(id,min(ch[0]->minid,ch[1]->minid));
		}
	};

	Node node[MAXN*2],*end;
	
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
		null->id=null->minid=MAXN;
		null->siz=0;
		null->rev=false;
	}
	Node *NewNode(int id) {
		*end=Node(id);
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
	int GetPathMini(Node *u,Node *v) {
		MakeRoot(u);
		Access(v);
		return v->minid;
	}
}

namespace FST {
	
	struct Node *null;
	struct Node {
		int num;
		Node *ch[2];
		Node() {
			ch[0]=ch[1]=null;
			num=0;
		}
		void PushUp() {
			num=ch[0]->num+ch[1]->num;
		}
	};
	
	Node node[MAXN*MAXLOG],*end;
	
	void Init() {
		null=node;
		null->ch[0]=null->ch[1]=null;
		end=node+1;
	}
	Node *NewNode() {
		*end=Node();
		return end++;
	}
	Node *CopyNode(Node *his) {
		*end=*his;
		return end++;
	}
	void Add(Node *&now,Node *his,int val,int L=0,int R=MAXN) {
		now=CopyNode(his);
		if(L==R) {
			now->num++;
			return;
		}
		int mid=(L+R)/2;
		if(val<=mid)
			Add(now->ch[0],his->ch[0],val,L,mid);
		else
			Add(now->ch[1],his->ch[1],val,mid+1,R);
		now->PushUp();
	}
	int Query(Node *now,Node *his,int l,int r,int L=0,int R=MAXN) {
		if(l<=L&&R<=r)
			return now->num-his->num;
		int mid=(L+R)/2,res=0;
		if(l<=mid)
			res+=Query(now->ch[0],his->ch[0],l,r,L,mid);
		if(mid<r)
			res+=Query(now->ch[1],his->ch[1],l,r,mid+1,R);
		return res;
	}
}

LCT::Node *ver[MAXN],*edge[MAXN];
FST::Node *root[MAXN];
pair<int,int> E[MAXN];

void add_edge(int u,int v,int i) {
	if(u==v) {
		FST::Add(root[i],root[i-1],i);
		return;
	}
	if(LCT::IsConnected(ver[u],ver[v])) {
		int j=LCT::GetPathMini(ver[u],ver[v]);
		FST::Add(root[i],root[i-1],j);
		Cut(ver[E[j].first],edge[j]);
		Cut(ver[E[j].second],edge[j]);
	}
	else
		FST::Add(root[i],root[i-1],0);
	Link(ver[u],edge[i]);
	Link(ver[v],edge[i]);
	return;
	
}

int main() {
	
	LCT::Init();
	FST::Init();
	int N,M,K,type;
	scanf("%d%d%d%d",&N,&M,&K,&type);
	for(int i=1;i<=N;i++)
		ver[i]=LCT::NewNode(MAXN);
	for(int i=1;i<=M;i++)
		edge[i]=LCT::NewNode(i);
	root[0]=FST::NewNode();
	for(int i=1,u,v;i<=M;i++) {
		scanf("%d%d",&u,&v);
		E[i]=make_pair(u,v);
		add_edge(u,v,i);
	}
	int ans=0;
	for(int i=1,l,r;i<=K;i++) {
		scanf("%d%d",&l,&r);
		if(type)
			l^=ans,r^=ans;
		ans=FST::Query(root[r],root[l-1],0,l-1);
		ans=N-ans;
		printf("%d\n",ans);
	}
	
	return 0;
}
