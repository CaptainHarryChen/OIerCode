#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005,MAXLOG=20;

int N,M;

struct Node *null;
struct Node
{
	int fa,dep;
	Node *ch[2];
};
Node nodes[MAXN*2*MAXLOG],*ntop,*root[MAXN];

Node *NewNode(Node *his)
{
	*ntop=*his;
	return ntop++;
}
void Build(Node *&now,int L=1,int R=N)
{
	now=NewNode(null);
	if(L==R)
	{
		now->fa=-1;
		now->dep=0;
		return;
	}
	int mid=(L+R)/2;
	Build(now->ch[0],L,mid);
	Build(now->ch[1],mid+1,R);
}
void Init()
{
	null=nodes;
	null->ch[0]=null->ch[1]=null;
	null->fa=-1;
	ntop=nodes+1;
	Build(root[0]);
}
void Modify(Node *his,Node *&now,int pos,int nval,int L=1,int R=N)
{
	now=NewNode(his);
	if(L==R)
	{
		now->fa=nval;
		return;
	}
	int mid=(L+R)/2;
	if(pos<=mid)
		Modify(his->ch[0],now->ch[0],pos,nval,L,mid);
	if(pos>mid)
		Modify(his->ch[1],now->ch[1],pos,nval,mid+1,R);
}
Node *Find(Node *now,int pos,int L=1,int R=N)
{
	if(L==R)
		return now;
	int mid=(L+R)/2;
	if(pos<=mid)
		return Find(now->ch[0],pos,L,mid);
	return Find(now->ch[1],pos,mid+1,R);
}
int Root(int now,int x,Node *&res=null)
{
	Node *r=root[now],*u;
	while(u=Find(r,x),u->fa!=-1)
		x=u->fa;
	if(res!=null)
		res=u;
	return x;
}
void Union(int his,int now,int x,int y)
{
	Node *u,*v;
	int r1=Root(his,x,u);
	int r2=Root(his,y,v);
	if(r1==r2)
		return;
	if(u->dep>v->dep)
		swap(u,v),swap(r1,r2);
	Modify(root[his],root[now],r1,r2);
	if(u->dep==v->dep)
		Find(root[now],r2)->dep++;//问题：为什么修改深度不新建结点？？？
}
bool Check(int now,int x,int y)
{return Root(now,x)==Root(now,y);}
void Debug(Node *now,int L=1,int R=N)
{
	if(L==R)
	{
		if(L==1)
			puts("Debug:start");
		printf("(%d,%d)",now->fa,now->dep);
		if(R==N)
			puts("\nDebug:end");
		return;
	}
	int mid=(L+R)/2;
	Debug(now->ch[0],L,mid);
	Debug(now->ch[1],mid+1,R);
}
int main()
{
	freopen("PersistentDSU_data.in","r",stdin);
	scanf("%d%d",&N,&M);
	Init();
	int op,a,b,k;
	int last=0;
	for(int i=1;i<=M;i++)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d",&a,&b);
			root[i]=root[last];
			Union(last,i,a,b);
		}
		if(op==2)
		{
			scanf("%d",&k);
			root[i]=root[k];
		}
		if(op==3)
		{
			scanf("%d%d",&a,&b);
			printf("%d\n",Check(last,a,b));
			root[i]=root[last];
		}
		last=i;
		//Debug(root[i]);
	}
	
	return 0;
}
