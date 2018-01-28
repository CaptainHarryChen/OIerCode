#include<cstdio>
const int MAXN=500005;

struct Node
{
	int key,siz;
	Node *ch[2],*fa;
	void Update()
	{siz=1+ch[0]->siz+ch[1]->siz;}
};
Node nodes[MAXN],*root,*ncnt,*null;

void Init()
{
	null=nodes;
	null->ch[0]=null->ch[1]=null->fa=null;
	root=null;
	ncnt=nodes+1;
}
Node *NewNode(int val)
{
	ncnt->key=val;ncnt->siz=1;
	ncnt->ch[0]=ncnt->ch[1]=ncnt->fa=null;
	return ncnt++;
}

void Rotate(Node *u)
{
	Node *v=u->fa;
	int d=v->ch[1]==u;
	
	u->fa=v->fa;
	if(v->fa!=null)
		v->fa->ch[v->fa->ch[1]==v]=u;
	
	v->ch[d]=u->ch[d^1];
	if(u->ch[d^1]!=null)
		u->ch[d^1]->fa=v;
	
	u->ch[d^1]=v;
	v->fa=u;
	
	if(v==root)
		root=u;
	v->Update();
	u->Update();
}
void Splay(Node *u,Node *rt)
{
	while(true)
	{
		Node *v=u->fa;
		Node *w=v->fa;
		if(v==rt)break;
		if(w==rt)
		{
			Rotate(u);
			break;
		}
		else
		{
			if((w->ch[1]==v)==(v->ch[1]==u))
				Rotate(v),Rotate(u);
			else
				Rotate(u),Rotate(u);
		}
	}
	u->Update();
}
Node *Find(int val)
{
	Node *u=root;
	int d;
	while(u!=null)
	{
		if(val==u->key)
			break;
		d=(val>u->key);
		if(u->ch[d]==null)
			break;
		u=u->ch[d];
	}
	Splay(u,null);
	return u;
}
Node *GetNear(Node *u,int t)
{
	u=u->ch[t];
	if(u==null)return null;
	while(u->ch[t^1]!=null)
		u=u->ch[t^1];
	return u;
}

void Insert(int val)
{
	if(root==null)
	{
		root=NewNode(val);
		return;
	}
	Node *u=root;
	int d;
	while(true)
	{
		d=(val>u->key);
		if(u->ch[d]==null)
			break;
		u=u->ch[d];
	}
	u->ch[d]=NewNode(val);
	u->ch[d]->fa=u;
	Splay(u,null);
}
void Delete(int val)
{
	Node *u=Find(val);
	Node *l=GetNear(u,0);
	Node *r=GetNear(u,1);
	if(l==null&&r==null)
		root=null;
	else if(l==null)
	{
		u->ch[1]->fa=null;
		root=u->ch[1];
	}
	else if(r==null)
	{
		u->ch[0]->fa=null;
		root=u->ch[0];
	}
	else
	{
		Splay(l,null);
		Splay(r,l);
		root->ch[1]->ch[0]=null;
		root->ch[1]->Update();
		root->Update();
	}
}
int GetRank(int val)
{
	Node *u=root;
	int res=0;
	while(true)
	{
		if(u->key<val)
			res+=u->ch[0]->siz+1;
		int d=(val>u->key);
		if(u->ch[d]==null)
			break;
		u=u->ch[d];
	}
	Splay(u,null);
	return res+1;
}
int GetKthNum(int k)
{
	Node *u=root;
	while(u!=null)
	{
		if(u->ch[0]->siz+1==k)
			break;
		if(u->ch[0]->siz+1<k)
		{
			k-=u->ch[0]->siz+1;
			u=u->ch[1];
		}
		else
			u=u->ch[0];
	}
	Splay(u,null);
	return u->key;
}
int GetPrev(int val)
{
	Node *u=Find(val-1);
	if(u->key>=val)
		u=GetNear(u,0);
	Splay(u,null);
	return u->key;
}
int GetNext(int val)
{
	Node *u=Find(val+1);
	if(u->key<=val)
		u=GetNear(u,1);
	Splay(u,null);
	return u->key;
}

int main()
{
	freopen("SplayTree_data.in","r",stdin);
	int n,op,v;
	scanf("%d",&n);
	Init();
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&op,&v);
		switch(op)
		{
			case 1:Insert(v);break;
			case 2:Delete(v);break;
			case 3:printf("%d\n",GetRank(v));break;
			case 4:printf("%d\n",GetKthNum(v));break;
			case 5:printf("%d\n",GetPrev(v));break;
			case 6:printf("%d\n",GetNext(v));break;
		}
	}
	return 0;
}
