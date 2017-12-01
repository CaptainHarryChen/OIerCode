#include<cstdio>
#include<cstdlib>
const int MAXN=500005;

struct Node//Treap's node
{
	int key,fix,siz;
	Node *lch,*rch;
	void Update()
	{siz=lch->siz+rch->siz+1;}
};

Node nodes[MAXN],*cur,*null,*root;

void Init()//initialization
{
	null=nodes;
	null->key=null->fix=null->siz=0;
	null->lch=null->rch=null;
	cur=nodes+1;
	root=null;
}
Node* newNode(int val)//create a node
{
	cur->key=val;cur->fix=rand();
	cur->siz=1;
	cur->lch=cur->rch=null;
	return cur++;
}
Node* Merge(Node *A,Node *B)//merge Treap A and Treap B, ensure max(A)<min(B)
{
	if(B==null)return A;
	if(A==null)return B;
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
void Insert(int val)//insert val
{
	Node *l,*r,*n;
	Split(val,l,r);
	n=newNode(val);
	root=Merge(Merge(l,n),r);
}
void Delete(int val)//delete val
{
	Node *l,*r,*d;
	Split(val,l,r);
	Split(val-1,l,d,l);
	root=Merge(Merge(l,Merge(d->lch,d->rch)),r);
}
int Getkth(int val)//return the rank of val, the val must exist
{
	Node *l,*r;
	Split(val-1,l,r);
	int ret=l->siz+1;
	root=Merge(l,r);
	return ret;
}
int Getkthnum(int k,Node *u=root)//return the kth number
{
	while(u!=null)
	{
		if(k<=u->lch->siz)
			u=u->lch;
		else if(k==u->lch->siz+1)
			return u->key;
		else
		{
			k=k-u->lch->siz-1;
			u=u->rch;
		}
	}
	return 0;
}
int Findpre(int val)//find the previous number of val ,it must exist
{
	Node *l,*r;
	Split(val-1,l,r);
	int k=l->siz;
	int ret=Getkthnum(k,l);
	root=Merge(l,r);
	return ret;
}
int Findnext(int val)//find the next number of val ,it must exist
{
	Node *l,*r;
	Split(val,l,r);
	int ret=Getkthnum(1,r);
	root=Merge(l,r);
	return ret;
}

int main()
{
	freopen("Treap_norotate_data.in","r",stdin);
    int n,opt,x;
    scanf("%d",&n);
	Init();
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&opt,&x);
        switch(opt)
        {
            case 1:Insert(x);break;
            case 2:Delete(x);break;
            case 3:printf("%d\n",Getkth(x));break;
            case 4:printf("%d\n",Getkthnum(x));break;
            case 5:printf("%d\n",Findpre(x));break;
            case 6:printf("%d\n",Findnext(x));break;
        }
    }
    return 0;
}
