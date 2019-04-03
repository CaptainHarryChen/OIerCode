//CQBZOJ3516
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500005,MAXLOG=20;

struct Node
{
    int key,fix;
    int siz;
    Node *son[2];
};
namespace Treap
{
    Node nodes[MAXN*MAXLOG];
    Node *it,*null,*root[MAXN];
    void Init()
    {
        null=nodes;
        null->son[0]=null->son[1]=null;
        it=nodes+1;
        fill(root,root+MAXN,null);
    }
    Node *NewNode(int v)
    {
        it->key=v;
        it->fix=rand();
        it->siz=1;
        it->son[0]=it->son[1]=null;
        return it++;
    }
    Node *NewNode(Node *u)
    {
        *it=*u;
        return it++;
    }
    void PushUp(Node *u)
    {u->siz=u->son[0]->siz+1+u->son[1]->siz;}
    void Split(int val,Node *&ansl,Node *&ansr,Node *u)
    {
        if(u==null)
        {
            ansl=ansr=null;
            return;
        }
        Node *t=NewNode(u);
        if(val<u->key)
        {
            Split(val,ansl,t->son[0],u->son[0]);
            ansr=t;
        }
        else
        {
            Split(val,t->son[1],ansr,u->son[1]);
            ansl=t;
        }
        PushUp(t);
    }
    Node *Merge(Node *u,Node *v)
    {
        if(u==null)return v;
        if(v==null)return u;
        if(u->fix<v->fix)
        {
            u->son[1]=Merge(u->son[1],v);
            PushUp(u);
            return u;
        }
        v->son[0]=Merge(u,v->son[0]);
        PushUp(v);
        return v;
    }
    void Insert(int his,int now,int x)
    {
        if(root[his]==null)
        {
            root[now]=NewNode(x);
            return;
        }
        Node *u=NewNode(x),*l,*r;
        Split(x,l,r,root[his]);
        root[now]=Merge(Merge(l,u),r);
    }
    void Delete(int his,int now,int x)
    {
        Node *l,*m,*r;
        Split(x,l,r,root[his]);
        Split(x-1,l,m,l);
        m=Merge(m->son[0],m->son[1]);
        root[now]=Merge(Merge(l,m),r);
    }
    void Copy(int his,int now)
    {root[now]=root[his];}
    int GetRank(int now,int x)
    {
        int rk=root[now]->son[0]->siz+1,res=0x3F3F3F3F;
        Node *u=root[now];
        while(u!=null)
        {
            if(x==u->key)
                res=rk;
            if(x<=u->key)
            {
                u=u->son[0];
                rk-=u->son[1]->siz+1;
            }
            else
            {
                u=u->son[1];
                rk+=u->son[0]->siz+1;
            }
        }
        return res;
    }
    int GetKthNum(int now,int k)
    {
        int rk=root[now]->son[0]->siz+1;
        Node *u=root[now];
        while(u!=null)
        {
            if(k==rk)
                return u->key;
            if(k<rk)
            {
                u=u->son[0];
                rk-=u->son[1]->siz+1;
            }
            else
            {
                u=u->son[1];
                rk+=u->son[0]->siz+1;
            }
        }
        return -1;
    }
    int GetPrev(int now,int x)
    {
        int res=-0x7FFFFFFF;
        Node *u=root[now];
        while(u!=null)
        {
            if(u->key<x)
            {
                res=max(res,u->key);
                u=u->son[1];
            }
            else
                u=u->son[0];
        }
        return res;
    }
    int GetNext(int now,int x)
    {
        int res=0x7FFFFFFF;
        Node *u=root[now];
        while(u!=null)
        {
            if(u->key>x)
            {
                res=min(res,u->key);
                u=u->son[0];
            }
            else
                u=u->son[1];
        }
        return res;
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    Treap::Init();
    for(int i=1;i<=n;i++)
    {
        int vi,op,x;
        scanf("%d%d%d",&vi,&op,&x);
        if(op==1)
            Treap::Insert(vi,i,x);
        else if(op==2)
            Treap::Delete(vi,i,x);
        else
            Treap::Copy(vi,i);
        if(op==3)
            printf("%d\n",Treap::GetRank(vi,x));
        else if(op==4)
            printf("%d\n",Treap::GetKthNum(vi,x));
        else if(op==5)
            printf("%d\n",Treap::GetPrev(vi,x));
        else if(op==6)
            printf("%d\n",Treap::GetNext(vi,x));
    }
    return 0;
}
