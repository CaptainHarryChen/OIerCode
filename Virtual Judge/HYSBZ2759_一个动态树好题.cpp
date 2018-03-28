#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=30005,MOD=10007;

void exgcd(int a,int b,int &x,int &y) {
	if(b==0) {
		x=1;y=0;
		return;
	}
	int xx,yy;
	exgcd(b,a%b,xx,yy);
	x=yy;
	y=xx-(a/b)*yy;
}
int inv(int x) {
	int a,b;
	exgcd((x%MOD+MOD)%MOD,MOD,a,b);
	return (a%MOD+MOD)%MOD;
}

struct Data {
	int k,b;
	Data(){}
	Data(int k,int b):k(k),b(b){}
	Data operator + (const Data &t)const
	{return Data(k*t.k%MOD,(b*t.k+t.b)%MOD);}
	int GetY(int x)
	{return (k*x+b)%MOD;}
};

struct Node *null;
struct Node {
	Data val,sum;
	Node *ch[2],*fa,*sfa;
	Node(){}
	Node(const Data &v) {
		val=sum=v;
		ch[0]=ch[1]=fa=sfa=null;
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
	void PushUp() {
		sum=ch[0]->sum+val+ch[1]->sum;
	}
};

Node node[MAXN],*end;

void Init() {
    end=node+1;
    null=node;
    null->sfa=null->fa=null->ch[0]=null->ch[1]=null;
    null->val=null->sum=Data(1,0);
}
Node *NewNode(Data v) {
    *end=Node(v);
    return end++;
}
void Rotate(Node *u) {
    Node *v=u->fa;
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
        u->SetChild(last,1);
        u->PushUp();
        last=u;
        u=u->fa;
    }
    Splay(s);
}
Node *FindRoot(Node *u) {
    Access(u);
    for(;u->ch[0]!=null;u=u->ch[0]);
    return u;
}
int Query(Node *u) {
	Node *root=FindRoot(u);
	//利用root->sfa->root环解出root的x值
	Access(root->sfa);
	Data d=root->sfa->sum;
	if(d.k==1)
		return d.b==0?-2:-1;
	int x=(MOD-d.b)*inv(d.k-1);
	x=(x%MOD+MOD)%MOD;
	Access(u);//得到root->u的算式
	return u->sum.GetY(x);//将root的x值代入式子求出答案
}
void Modify(Node *u,Node *f,Data d) {
	Node *root=FindRoot(u);//已经Access(u)了
	u->val=d;
	u->PushUp();
	if(u==root)//u为根，剪断环
		u->sfa=null;
	else {
		Access(u);
		u->ch[0]->fa=null;//切断u与父结点的边
		u->ch[0]=null;
		u->PushUp();
		if(FindRoot(root->sfa)!=root) {//u在环上
			Access(root);
			root->fa=root->sfa;
			root->sfa=null;
		}
	}
	Access(u);
	if(FindRoot(f)==u)//u与f已连接，将形成环
		u->sfa=f;
	else
		u->fa=f;
}

int N,Q;
int fa[MAXN];
Node *id[MAXN];
int mk,vis[MAXN];

void DFS(int u) {
	vis[u]=mk;
	if(vis[fa[u]]==mk) {
		id[u]->sfa=id[fa[u]];
		return;
	}
	id[u]->fa=id[fa[u]];
	if(!vis[fa[u]])
		DFS(fa[u]);
}

int main() {
	Init();
	scanf("%d",&N);
	Data d;
	for(int i=1;i<=N;i++) {
		scanf("%d%d%d",&d.k,&fa[i],&d.b);
		id[i]=NewNode(d);
	}
	for(int i=1;i<=N;i++)
		if(!vis[i])
			mk++,DFS(i);
	scanf("%d",&Q);
	char op[5];
	int a,f;
	for(int i=1;i<=Q;i++) {
		scanf("%s%d",op,&a);
		if(op[0]=='A')
			printf("%d\n",Query(id[a]));
		else {
			scanf("%d%d%d",&d.k,&f,&d.b);
			Modify(id[a],id[f],d);
		}
	}
	return 0;
}
