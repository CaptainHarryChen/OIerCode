#include<cstdio>
#define MAXN 500005
template<class Data>
struct SplayTree
{
	struct Node
	{
		Data x;
		int cnt,size;
		Node *son[2],*fa;
		Node(){}
		Node(Data x,Node *fa):x(x),fa(fa){son[0]=son[1]=NULL;cnt=size=1;}
		void Update()
		{
			size=cnt;
			if(son[0])size+=son[0]->size;
			if(son[1])size+=son[1]->size;
		}
	}*root,_new[MAXN];
	int top;
	SplayTree(){root=NULL;top=0;}
	Node *newNode(Data x,Node *fa)
	{
		_new[top++]=Node(x,fa);
		return _new+top-1;
	}
	int cmp(Data x,Data y){return x==y?-1:x>y;}
	Node *Find(Data x)
	{
		Node *u=root;
		int d;
		while(u)
		{
			d=cmp(x,u->x);
			if(d==-1)return u;
			if(u->son[d]==NULL)return u;
			u=u->son[d];
		}
		return NULL;
	}
	Node *getLastNext(Node *u,int d)
	{
		Node *ret=u->son[d];
		while(ret&&ret->son[!d])ret=ret->son[!d];
		return ret;
	}
	void Rotate(Node *y,int d)
	{
		Node *x=y->fa;
		x->son[!d]=y->son[d];
		if(y->son[d])y->son[d]->fa=x;
		y->fa=x->fa;
		if(x->fa)x->fa->son[x->fa->son[1]==x]=y;
		y->son[d]=x;x->fa=y;
		if(root==x)root=y;
		x->Update();
	}
	void Splay(Node *x,Node *rt)
	{
		Node *y,*z;
		while(x->fa!=rt)
		{
			y=x->fa;
			z=y->fa;
			if(z==rt)
				Rotate(x,y->son[0]==x);
			else if((y->son[0]==x)==(z->son[0]==y))
			{
				Rotate(y,z->son[0]==y);
				Rotate(x,y->son[0]==x);
			}
			else
			{
				Rotate(x,y->son[0]==x);
				Rotate(x,z->son[0]==x);
			}
		}
		x->Update();
	}
	void Insert(Data x)
	{
		if(root==NULL)
		{root=newNode(x,NULL);return;}
		Node *u=root;
		int d;
		while(u)
		{
			d=cmp(x,u->x);
			if(d==-1)
			{
				u->cnt++;
				Splay(u,NULL);
				return;
			}
			if(u->son[d])u=u->son[d];
			else
			{
				u->son[d]=newNode(x,u);
				Splay(u->son[d],NULL);
				return;
			}
		}
	}
	void Delete(Data x)
	{
		Node *u=root;
		int d;
		while(u)
		{
			d=cmp(x,u->x);
			if(d==-1)
			{
				Splay(u,NULL);
				if(u->cnt>1)
				{u->cnt--;u->size--;}
				else
				{
					Node *lst,*nxt;
					lst=getLastNext(u,0);
					nxt=getLastNext(u,1);
					if(!lst&&!nxt)root=NULL;
					else if(!lst)
					{
						root=root->son[1];
						root->fa=NULL;
					}
					else if(!nxt)
					{
						root=root->son[0];
						root->fa=NULL;
					}
					else
					{
						Splay(lst,NULL);
						Splay(nxt,root);
						root->son[1]->son[0]=NULL;
						root->son[1]->size--;
					}
				}
				break;
			}
			else u=u->son[d];
		}
	}
	int QueryRank(Data x)
	{
		Node *u=Find(x);
		Splay(u,NULL);
		int ret=1;
		if(u->son[0])ret+=u->son[0]->size;
		return ret;
	}
	Data QueryNum(int rank)
	{
		Node *u=root;
		int temp=1;
		if(u->son[0])temp+=u->son[0]->size;
		while(u)
		{
			if(rank<temp)
			{
				u=u->son[0];
				temp-=u->cnt;
				if(u->son[1])temp-=u->son[1]->size;
			}
			else if(rank>=temp&&rank<temp+u->cnt)
			{
				Splay(u,NULL);
				return u->x;
			}
			else
			{
				temp+=u->cnt;
				u=u->son[1];
				if(u->son[0])temp+=u->son[0]->size;
			}
		}
		return root->x;
	}
	Data Last(Data x)
	{
		Node *u=Find(x);
		Splay(u,NULL);
		if(u->x<x)return u->x;
		return getLastNext(u,0)->x;
	}
	Data Next(Data x)
	{
		Node *u=Find(x);
		Splay(u,NULL);
		if(u->x>x)return u->x;
		return getLastNext(u,1)->x;
	}
};
SplayTree< int > T;
int main()
{
	freopen("SplayTree_data.in","r",stdin);
	int n,x,op;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&op,&x);
        switch(op)
        {
            case 1:T.Insert(x);break;
            case 2:T.Delete(x);break;
            case 3:printf("%d\n",T.QueryRank(x));break;
            case 4:printf("%d\n",T.QueryNum(x));break;
            case 5:printf("%d\n",T.Last(x));break;
            case 6:printf("%d\n",T.Next(x));break;
        }
    }
    return 0;
}
