#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

namespace LT
{
	struct Node *null;
	struct Node
	{
		int val,id;
		int siz,dis;
		Node *ch[2];
		void PushUp()
		{
			siz=ch[0]->siz+1+ch[1]->siz;
			dis=ch[1]->dis+1;
		}
	};
	Node nodes[MAXN],*ntop;

	void Init()
	{
		null=nodes;
		null->val=null->siz=null->dis=0;
		null->ch[0]=null->ch[1]=null;
		ntop=nodes+1;
	}
	Node *NewNode(int val,int id)
	{
		ntop->val=val;ntop->id=id;
		ntop->siz=1;ntop->dis=0;
		ntop->ch[0]=ntop->ch[1]=null;
		return ntop++;
	}
	Node *Merge(Node *u,Node *v)
	{
		if(u==null)
			return v;
		if(v==null)
			return u;
		if(u->val>v->val)
			swap(u,v);
		u->ch[1]=Merge(u->ch[1],v);
		if(u->ch[1]->dis>u->ch[0]->dis)
			swap(u->ch[0],u->ch[1]);
		u->PushUp();
		return u;
	}
	void Pop(Node *&u)
	{
		u=Merge(u->ch[0],u->ch[1]);
	}
	pair<int,int> Top(Node *u)
	{return make_pair(u->id,u->val);}
}
namespace DSU
{
	int fa[MAXN];
	int Root(int x)
	{return fa[x]==0?x:(fa[x]=Root(fa[x]));}
	void Merge(int x,int y)
	{fa[y]=x;}
}

LT::Node *group[MAXN];
bool dead[MAXN];

int main()
{
	int n,m;
	scanf("%d",&n);
	LT::Init();
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		group[i]=LT::NewNode(x,i);
	}
	scanf("%d",&m);
	char op[3];
	int x,y;
	for(int i=1;i<=m;i++)
	{
		scanf("%s%d",op,&x);
		if(op[0]=='M')
		{
			scanf("%d",&y);
			if(dead[x]||dead[y])
				continue;
			int r1=DSU::Root(x),r2=DSU::Root(y);
			if(r1==r2)
				continue;
			group[r1]=LT::Merge(group[r1],group[r2]);
			DSU::Merge(r1,r2);
		}
		if(op[0]=='K')
		{
			if(dead[x])
			{
				puts("0");
				continue;
			}
			int r=DSU::Root(x);
			pair<int,int> man=LT::Top(group[r]);
			LT::Pop(group[r]);
			dead[man.first]=true;
			printf("%d\n",man.second);
		}
	}
	
	return 0;
}
