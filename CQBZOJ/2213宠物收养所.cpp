#include<cstdio>
#include<cstdlib>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?b:a)
#define MAXN 80005
#define MOD 1000000
class Treap
{
public:
	struct Node
	{
		int x,cnt,size,pri;
		bool flag;
		Node *son[2];
		Node(){son[0]=son[1]=0;cnt=size=pri=0;pri=rand();}
		Node(int x,bool flag):x(x),flag(flag){cnt=size=1;son[0]=son[1]=0;pri=rand();}
		void Update()
		{
			size=cnt;
			if(son[0])size+=son[0]->size;
			if(son[1])size+=son[1]->size;
		}
	}*root,_new[MAXN];
	int top;
	Treap(){root=NULL;top=0;}
	Node *newNode(int x,bool flag)
	{
		_new[top++]=Node(x,flag);
		return _new+top-1;
	}
	int cmp(int x,int y)
	{return x==y?-1:x>y;}
	Node *Find(int x)
	{
		Node *p=root;
		int d;
		while(p)
		{
			d=cmp(x,p->x);
			if(d==-1)return p;
			p=p->son[d];
		}
		return NULL;
	}
	void Rotate(Node *&p,int d)
	{
		Node *y=p->son[!d];
		p->son[!d]=y->son[d];
		y->son[d]=p;
		p->Update();
		y->Update();
		p=y;
	}
	void Insert(Node *&p,int x,bool flag)
	{
		if(!p)
		{p=newNode(x,flag);}
		else
		{
			int k=cmp(x,p->x);
			if(k==-1)
			{p->cnt++;p->size++;}
			else
			{
				Insert(p->son[k],x,flag);
				if(p->son[k]->pri<p->pri)
					Rotate(p,!k);
			}
			p->Update();
		}
	}
	void Delete(Node *&p,int x)
	{
		if(!p)return;
		int k=cmp(x,p->x);
		if(k==-1)
		{
			if(p->cnt>1)
			{p->cnt--;p->size--;}
			else if(!p->son[1])
				p=p->son[0];
			else if(!p->son[0])
				p=p->son[1];
			else
			{
				int d=cmp(p->son[0]->pri,p->son[1]->pri);
				Rotate(p,!d);
				Delete(p->son[!d],x);
			}
		}
		else Delete(p->son[k],x);
		if(p)p->Update();
	}
	int QueryRank(int num)
	{
		Node *p=root;
		int ret=1,d;
		if(p->son[0])ret+=p->son[0]->size;
		while(p)
		{
			d=cmp(num,p->x);
			if(d==-1)return ret;
			if(d==0)
			{
				p=p->son[0];
				ret-=p->cnt;
				if(p->son[1])
					ret-=p->son[1]->size;
			}
			if(d==1)
			{
				ret+=p->cnt;
				p=p->son[1];
				if(p->son[0])
					ret+=p->son[0]->size;
			}
		}
		return ret;
	}
	int QueryNum(int rank)
	{
		Node *p=root;
		int r=1;
		if(p->son[0])r+=p->son[0]->size;
		while(p)
		{
			if(rank<r)
			{
				p=p->son[0];
				r-=p->cnt;
				if(p->son[1])
					r-=p->son[1]->size;
			}
			else if(rank>=r&&rank<r+p->cnt)
				return p->x;
			else
			{
				r+=p->cnt;
				p=p->son[1];
				if(p->son[0])
					r+=p->son[0]->size;
			}
		}
		return -1;
	}
	int Last(int x)
	{
		Node *p=root;
		int d,mx=-0x3FFFFFFF;
		while(p)
		{
			d=cmp(x,p->x);
			if(d==-1)break;
			if(p->x<x)mx=max(mx,p->x);
			if(!p->son[d])break;
			p=p->son[d];
		}
		if(p->son[0])
		{
			p=p->son[0];
			while(p->son[1])p=p->son[1];
			mx=max(mx,p->x);
		}
		return mx;
	}
	int Next(int x)
	{
		Node *p=root;
		int d,mn=0x3FFFFFFF;
		while(p)
		{
			d=cmp(x,p->x);
			if(d==-1)break;
			if(p->x>x)mn=min(mn,p->x);
			if(!p->son[d])break;
			p=p->son[d];
		}
		if(p->son[1])
		{
			p=p->son[1];
			while(p->son[0])p=p->son[0];
			mn=min(mn,p->x);
		}
		return mn;
	}
}T;
int main()
{
	srand(314159265);
	int n,x,op,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&op,&x);
		if(op==0)
		{
			if(!T.root||T.root->flag==0)
				T.Insert(T.root,x,op);
			else
			{
				Treap::Node *p=T.Find(x);
				if(p){T.Delete(T.root,x);continue;}
				int lst=T.Last(x),nxt=T.Next(x);
				if(x-lst<=nxt-x)
				{
					ans=(ans+(x-lst))%MOD;
					T.Delete(T.root,lst);
				}
				else
				{
					ans=(ans+(nxt-x))%MOD;
					T.Delete(T.root,nxt);
				}
			}
		}
		else
		{
			if(!T.root||T.root->flag==1)
				T.Insert(T.root,x,op);
			else
			{
				Treap::Node *p=T.Find(x);
				if(p){T.Delete(T.root,x);continue;}
				int lst=T.Last(x),nxt=T.Next(x);
				if(x-lst<=nxt-x)
				{
					ans=(ans+(x-lst))%MOD;
					T.Delete(T.root,lst);
				}
				else
				{
					ans=(ans+(nxt-x))%MOD;
					T.Delete(T.root,nxt);
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
