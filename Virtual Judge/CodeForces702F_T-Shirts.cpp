#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int MAXN=200005;
 
struct Node//Treap's node
{
	int key,fix,siz,add,cnt,cnts,id;
	Node *lch,*rch;
	Node(){}
	Node(int k,Node *nul)
	{key=k;fix=rand();siz=1;add=cnt=cnts=0;lch=rch=nul;}
	void Update()
	{siz=1+lch->siz+rch->siz;}
};
 
Node nodes[MAXN],*cur,*null,*root;

void PushDown(Node *u)
{
	u->key-=u->add;
	if(u->lch!=null)
	{u->lch->add+=u->add;u->lch->cnt+=u->cnts;u->lch->cnts+=u->cnts;}
	if(u->rch!=null)
	{u->rch->add+=u->add;u->rch->cnt+=u->cnts;u->rch->cnts+=u->cnts;}
	u->add=u->cnts=0;
}
void Init()//initialization
{
    null=nodes;
    null->key=null->fix=null->siz=0;
    null->lch=null->rch=null;
    cur=nodes+1;
    root=null;
}
Node* newNode(int val,int cnt,int id)//create a node
{
    cur->key=val;cur->fix=rand();
    cur->siz=1;cur->cnt=cnt;cur->id=id;
    cur->lch=cur->rch=null;
    return cur++;
}
Node* Merge(Node *A,Node *B)//merge Treap A and Treap B, ensure max(A)<min(B)
{
    if(B==null)return A;
    if(A==null)return B;
	PushDown(A);
	PushDown(B);
    if(A->fix<B->fix)
    {
        A->rch=Merge(A->rch,B);
        A->Update();
        return A;
    }
    B->lch=Merge(A,B->lch);
    B->Update();
    return B;
}
void Split(int val,Node *&ansl,Node *&ansr,Node *u=root)//split Treap u by val, then the two part of Treap u will be saved in ansl and ansr
{
    if(u==null)
    {
        ansl=ansr=null;
        return;
    }
	PushDown(u);
    if(val<u->key)
    {
        Split(val,ansl,u->lch,u->lch);
        u->Update();
        ansr=u;
    }
    else
    {
        Split(val,u->rch,ansr,u->rch);
        u->Update();
        ansl=u;
    }
}
void Insert(int val,int cnt,int id,Node *&u=root)//insert val
{
    Node *l,*r,*n;
    Split(val,l,r,u);
    n=newNode(val,cnt,id);
    u=Merge(Merge(l,n),r);
}
void Debug(Node *u=root)
{
	if(u==null)return;
	PushDown(u);
	Debug(u->lch);
	printf("%d ",u->key);
	Debug(u->rch);
}

struct Tshirt
{
	int c,q;
	bool operator < (const Tshirt &t)const
	{return q>t.q||(q==t.q&&c<t.c);}
};

void dfs(Node *in,Node *&rt)
{
	if(in==null)return;
	PushDown(in);
	dfs(in->lch,rt);
	dfs(in->rch,rt);
	
	Node *l,*r,*n;
    Split(in->key,l,r,rt);
    n=in;n->lch=n->rch=null;
    rt=Merge(Merge(l,in),r);
}
void Work(const Tshirt &op)
{
	Node *none,*buy;
	Split(op.c-1,none,buy);
	Node *l;
	Split(op.c*2-1,l,buy,buy);
	if(l!=null){l->cnt++;l->cnts++;l->add+=op.c;}
	if(buy!=null){buy->cnt++;buy->cnts++;buy->add+=op.c;}
	dfs(l,none);
	root=Merge(none,buy);
}

Tshirt Ts[MAXN];
int ans[MAXN];

void getans(Node *u)
{
	if(u==null)return;
	ans[u->id]=u->cnt;
	PushDown(u);
	getans(u->lch);
	getans(u->rch);
}

int main()
{
	int n;
	Init();
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&Ts[i].c,&Ts[i].q);
	sort(Ts+1,Ts+n+1);
	int k,b;
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&b);
		Insert(b,0,i);
	}
	for(int i=1;i<=n;i++)
	{
		Work(Ts[i]);
		//Debug();
		//puts("");
	}
	getans(root);
	for(int i=1;i<=k;i++)
		printf("%d ",ans[i]);
	puts("");
	return 0;
}
