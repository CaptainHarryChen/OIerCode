#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define MAXN 500005
#define INF 0x7FFFFFFF
#define LUCKY_NUM 20010919
using std::max;
using std::min;
struct Node
{
	int x,pri,cnt,size;
	Node *son[2];
	Node(){son[0]=son[1]=NULL;pri=x=cnt=size=0;}
	Node(int x):x(x){son[0]=son[1]=NULL;pri=rand();cnt=size=1;}
	Node(int x,int pri):x(x),pri(pri){son[0]=son[1]=NULL;cnt=size=1;}
	void Update()
	{
		size=cnt;
		if(son[0])size+=son[0]->size;
		if(son[1])size+=son[1]->size;
	}
};
class Treap
{
public:
	Node *root;
	Treap():root(NULL){}
	int cmp(int x,int y){if(x==y)return -1;return x>y?1:0;}
	void Rotate(Node *&x,int d)
	{
		Node *y=x->son[!d];
		x->son[!d]=y->son[d];
		x->Update();
		y->son[d]=x;
		y->Update();
		x=y;
	}
	void Insert(Node *&id,int x)
	{
		if(!id)
			id=new Node(x);
		else
		{
			int d=cmp(x,id->x);
			if(d==-1){id->cnt++;id->size++;}
			else
			{
				Insert(id->son[d],x);
				id->size++;
				if(id->son[d]->pri<id->pri)
					Rotate(id,!d);
			}
		}
	}
	void Delete(Node *&id,int x)
	{
		if(!id)return;
		int d=cmp(x,id->x);
		if(d==-1)
		{
			Node *t=id;
			if(id->cnt>1)
				id->cnt--;
			else if(id->son[0]==NULL)
			{
				id=id->son[1];
				delete t;
			}
			else if(id->son[1]==NULL)
			{
				id=id->son[0];
				delete t;
			}
			else
			{
				int k=id->son[0]->pri>id->son[1]->pri?1:0;
				Rotate(id,k);
				Delete(id->son[k],x);
			}
		}
		else Delete(id->son[d],x);
		if(id)
			id->Update();
	}
	int Query_rank(int x)
	{
		Node *id=root;
		int rank=0,d;
		while(id)
		{
			d=cmp(x,id->x);
			if(d==0)id=id->son[0];
			else if(d==-1)
			{
				if(id->son[0])
					rank+=id->son[0]->size;
				break;
			}
			else if(d==1)
			{
				if(id->son[0])
					rank+=id->son[0]->size;
				rank+=id->cnt;
				id=id->son[1];
			}
		}
		return rank+1;
	}
	int Query_num(int rank)
	{
		Node *id=root;
		int now=1;
		if(id->son[0])
			now+=id->son[0]->size;
		while(id)
		{
			if(rank>=now&&rank<now+id->cnt)
				return id->x;
			else if (rank<now)
			{
				id=id->son[0];
				now=now-id->cnt;
				if(id->son[1])
					now-=id->son[1]->size;
			}
			else
			{
				now+=id->cnt;
				id=id->son[1];
				if(id->son[0])
					now+=id->son[0]->size;
			}
		}
		return -1;
	}
	int Last(int x)
	{
		int la=-INF,d;
		Node *id=root;
		while(id)
		{
			d=cmp(x,id->x);
			if(d==-1)break;
			if(id->x<x)la=max(la,id->x);
			if(!id->son[d])break;
			id=id->son[d];
		}
		if(id->son[0])
		{
			id=id->son[0];
			while(id->son[1])
				id=id->son[1];
			la=max(la,id->x);
		}
		return la;
	}
	int Next(int x)
	{
		int ne=INF,d;
		Node *id=root;
		while(id)
		{
			d=cmp(x,id->x);
			if(d==-1)break;
			if(id->x>x)ne=min(ne,id->x);
			if(!id->son[d])break;
			id=id->son[d];
		}
		if(id->son[1])
		{
			id=id->son[1];
			while(id->son[0])
				id=id->son[0];
			ne=min(ne,id->x);
		}
		return ne;
	}
};
int main()
{
	srand(LUCKY_NUM);
	int n;
	Treap T;
	scanf("%d",&n);
	for(int i=1,op,x;i<=n;i++)
	{
		scanf("%d%d",&op,&x);
		switch(op)
		{
			case 1:T.Insert(T.root,x);break;
			case 2:T.Delete(T.root,x);break;
			case 3:printf("%d\n",T.Query_rank(x));break;
			case 4:printf("%d\n",T.Query_num(x));break;
			case 5:printf("%d\n",T.Last(x));break;
			case 6:printf("%d\n",T.Next(x));break;
		}
	}
	return 0;
}
