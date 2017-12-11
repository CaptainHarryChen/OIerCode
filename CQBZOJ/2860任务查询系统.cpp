#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXLOG=18;

struct Node
{
	int key,fix,siz;
	long long sum;
	Node *lch,*rch;
	void Update()
	{
		sum=1LL*key+lch->sum+rch->sum;
		siz=1+lch->siz+rch->siz;
	}
};
Node nodes[MAXN*2*MAXLOG*2],*cur,*null,*root[MAXN];
void Init()
{
	null=nodes;
	memset(null,0,sizeof(Node));
	null->lch=null->rch=null;
	cur=nodes+1;
	root[0]=null;
}
Node* Merge(Node *A,Node *B)
{
	if(A==null)return B;
	if(B==null)return A;
	Node *t;
	if(A->fix<=B->fix)
		A->rch=Merge(A->rch,B),t=A;
	else
		B->lch=Merge(A,B->lch),t=B;
	t->Update();
	return t;
}
void Split(Node *rt,int k,Node *&ansL,Node *&ansR)
{
	if(rt==null)
	{
		ansL=ansR=null;
		return;
	}
	int rk=rt->lch->siz+1;
	Node *t;
	t=cur++;*t=*rt;
	if(k<rk)
	{
		Split(rt->lch,k,ansL,ansR);
		t->lch=ansR;
		ansR=t;
	}
	else
	{
		Split(rt->rch,k-rt->lch->siz-1,ansL,ansR);
		t->rch=ansL;
		ansL=t;
	}
	t->Update();
}
int GetRank(Node *rt,int val)
{
	Node *u=rt;
	int res=0,flag=0;
	while(u!=null)
	{
		if(u->key<val)
		{
			res+=u->lch->siz+1;
			u=u->rch;
		}
		else
		{
			if(u->key==val)flag=1;
			u=u->lch;
		}
	}
	return res+flag;
}
int Sumkth(int id,int k)
{
	int res=0;
	Node *u=root[id];
	while(u!=null)
	{
		if(k>=u->lch->siz+1)
		{
			res+=u->lch->sum+u->key;
			k-=u->lch->siz+1;
			u=u->rch;
		}
		else
			u=u->lch;
	}
	return res;
}
void Insert(int now,int val)
{
	int k=GetRank(root[now],val);
	Node *nl,*nr;
	Split(root[now],k,nl,nr);
	Node *n=cur++;
	n->key=val;n->fix=rand();
	n->lch=n->rch=null;
	n->Update();
	root[now]=Merge(Merge(nl,n),nr);
}
void Delete(int now,int val)
{
	int k=GetRank(root[now],val);
	Node *nl,*n,*nr;
	Split(root[now],k-1,nl,n);
	Split(n,1,n,nr);
	root[now]=Merge(nl,nr);
}

struct OP
{
	int ti,val;
	bool type;
	OP(){}
	OP(int t,int v,bool ty)
	{ti=t;val=v;type=ty;}
	bool operator < (const OP &b)const
	{return ti<b.ti;}
};
OP task[MAXN*2];
int run[MAXN];

int main()
{
	int m,n;
	scanf("%d%d",&m,&n);
	
	int s,e,p;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&s,&e,&p);
		run[s]++;run[e+1]--;
		task[i*2-1]=OP(s,p,1);
		task[i*2]=OP(e+1,p,0);
	}
	sort(task+1,task+2*m+1);
	
	Init();
	for(int i=1,j=1;i<=n;i++)
	{
		run[i]+=run[i-1];
		root[i]=null;
		if(root[i-1]->siz!=0)
		{
			root[i]=cur++;
			*root[i]=*root[i-1];
		}
		while(task[j].ti==i&&j<=2*m)
		{
			if(task[j].type)
				Insert(i,task[j].val);
			else
				Delete(i,task[j].val);
			j++;
		}
	}
	
	int x,a,b,c,k;
	long long ans=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d",&x,&a,&b,&c);
		k=1+(ans*a+b)%c;
		if(k>=run[x])
			printf("%lld\n",ans=root[x]->sum);
		else
			printf("%lld\n",ans=Sumkth(x,k));
	}
	
    return 0;
}
