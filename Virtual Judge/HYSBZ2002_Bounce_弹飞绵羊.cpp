#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 200005
namespace LCT
{
	struct Node
	{
		int val,size;
		Node *fa,*son[2];
		bool prefer;
	}nodes[MAXN];
	void Update(Node *u)
	{
		u->size=1;
		if(u->son[0])u->size+=u->son[0]->size;
		if(u->son[1])u->size+=u->son[1]->size;
	}
	void Rotate(Node *x,int d)
	{
		Node *y=x->fa;
		x->fa=y->fa;
		x->prefer=y->prefer;
		if(y->prefer)y->fa->son[y->fa->son[1]==y]=x;
		y->fa=x;
		y->prefer=1;
		y->son[!d]=x->son[d];
		if(x->son[d])x->son[d]->fa=y;
		x->son[d]=y;
		Update(y);
	}
	void Splay(Node *x)
	{
		Node *y,*z;
		int d1,d2;
		while(x->prefer)
		{
			y=x->fa;
			if(!y->prefer)
			{
				Rotate(x,y->son[0]==x);
				break;
			}
			z=y->fa;
			d1=(z->son[0]==y);
			d2=(y->son[0]==x);
			if(d1==d2)
			{
				Rotate(y,d1);
				Rotate(x,d2);
			}
			else
			{
				Rotate(x,d2);
				Rotate(x,d1);
			}
		}
		Update(x);
	}
	void Access(Node *u)
	{
		Node *last=NULL;
		while(u)
		{
			Splay(u);
			if(u->son[1])
				u->son[1]->prefer=0;
			u->son[1]=last;
			if(u->fa)u->prefer=1;
			last=u;
			u=u->fa;
		}
	}
}
int main()
{
	int n,m,x,val,i,op,ans;
	LCT::Node *u,*v;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&x);
		if(i+x>=n)continue;
		LCT::nodes[i].fa=LCT::nodes+i+x;
		LCT::nodes[i].size=1;
	}
	scanf("%d",&m);
	for(i=1;i<=m;i++)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d",&x);
			u=LCT::nodes+x;
			LCT::Access(u);
			LCT::Splay(u);
			ans=0;
			if(u->son[0])ans+=u->son[0]->size;
			ans++;
			printf("%d\n",ans);
		}
		else
		{
			scanf("%d%d",&x,&val);
			u=LCT::nodes+x;
			LCT::Access(u);
			LCT::Splay(u);
			if(u->son[0])
			{
				v=u->son[0];
				v->fa=NULL;
				v->prefer=0;
				u->son[0]=NULL;
				LCT::Update(u);
			}
			if(x+val<n)
				u->fa=LCT::nodes+x+val;
		}
	}
	return 0;
}
