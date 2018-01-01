#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=500005,MAXLOG=20;

struct Node
{
    int key;
    int fix,siz;
    Node *lch,*rch;
    Node(){}
    Node(int k,Node *nul)
    {key=k;fix=rand();siz=1;lch=rch=nul;}
    void Update()
    {siz=1+lch->siz+rch->siz;}
};
Node nodes[MAXN*MAXLOG],*cur,*null,*root[MAXN];
Node *NewNode(Node *v)
{*cur=*v;cur++;return cur-1;}
Node *NewNode(int val)
{*cur=Node(val,null);cur++;return cur-1;}
void Init()
{
    null=nodes;
    *null=Node(0,null);
    null->fix=0;
    null->siz=0;
    cur=nodes+1;
    root[0]=null;
}
Node *Merge(Node *A,Node *B)
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
void Split(Node *rt,int val,Node *&ansL,Node *&ansR)
{
    if(rt==null){ansL=null;ansR=null;return;}
    Node *t=NewNode(rt);
    if(val<rt->key)
    {
        Split(rt->lch,val,ansL,ansR);
        t->lch=ansR;
        ansR=t;
    }
    else
    {
        Split(rt->rch,val,ansL,ansR);
        t->rch=ansL;
        ansL=t;
    }
    t->Update();
}
void Insert(int his,int now,int val)
{
    if(root[his]!=null)
        root[now]=NewNode(root[his]);
    Node *nl,*n,*nr;
    Split(root[now],val,nl,nr);
    n=NewNode(val);
    root[now]=Merge(Merge(nl,n),nr);
}
void Delete(int his,int now,int val)
{
    if(root[his]!=null)
        root[now]=NewNode(root[his]);
    Node *nl,*n,*nr;
    Split(root[now],val-1,nl,nr);
    Split(nr,val,n,nr);
    if(n->key==val)
        n=Merge(n->lch,n->rch);
    root[now]=Merge(Merge(nl,n),nr);
}
int GetRank(int id,int val)
{
    Node *u=root[id];
    int res=0;
    while(u!=null)
    {
        if(val<=u->key)
        {
            u=u->lch;
        }
        else
        {
            res+=u->lch->siz+1;
            u=u->rch;
        }
    }
    return res+1;
}
int GetKthNum(int id,int k)
{
    Node *u=root[id];
    while(u!=null)
    {
        int rk=u->lch->siz+1;
        if(k<rk)
            u=u->lch;
        else if(k==rk)
            return u->key;
        else
        {
            k-=rk;
            u=u->rch;
        }
    }
    return 0;
}
int FindPrev(int id,int val)
{
    Node *u=root[id];
    int res=-0x7FFFFFFF;
    while(u!=null)
    {
        if(u->key<val)
        {
            res=max(res,u->key);
            u=u->rch;
        }
        else
            u=u->lch;
    }
    return res;
}
int FindNext(int id,int val)
{
    Node *u=root[id];
    int res=0x7FFFFFFF;
    while(u!=null)
    {
        if(u->key>val)
        {
            res=min(res,u->key);
            u=u->lch;
        }
        else
            u=u->rch;
    }
    return res;
}

int main()
{
    int n,v,opt,x;
    Init();
    Insert(0,0,0x7FFFFFFF);
    Insert(0,0,-0x7FFFFFFF);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&v,&opt,&x);
        root[i]=root[v];
        switch(opt)
        {
            case 1:
                Insert(v,i,x);
                break;
            case 2:
                Delete(v,i,x);
                break;
            case 3:
                printf("%d\n",GetRank(v,x)-1);
                break;
            case 4:
                printf("%d\n",GetKthNum(v,x+1));
                break;
            case 5:
                printf("%d\n",FindPrev(v,x));
                break;
            case 6:
                printf("%d\n",FindNext(v,x));
                break;
        }
    }
    return 0;
}
