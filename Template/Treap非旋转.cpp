#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500005;

struct Node
{
    int key,fix;
    int siz;
    Node *son[2];
};
namespace Treap
{
    Node nodes[MAXN];
    Node *it,*null,*root;
    void Init()
    {
        null=nodes;
        null->son[0]=null->son[1]=null;
        it=nodes+1;
        root=null;
    }
    Node *NewNode(int v)
    {
        it->key=v;
        it->fix=rand();
        it->siz=1;
        it->son[0]=it->son[1]=null;
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
        if(val<u->key)
        {
            Split(val,ansl,u->son[0],u->son[0]);
            ansr=u;
        }
        else
        {
            Split(val,u->son[1],ansr,u->son[1]);
            ansl=u;
        }
        PushUp(u);
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
    void Insert(int x)
    {
        if(root==null)
        {
            root=NewNode(x);
            return;
        }
        Node *u=NewNode(x),*l,*r;
        Split(x,l,r,root);
        root=Merge(Merge(l,u),r);
    }
    void Delete(int x)
    {
        Node *l,*m,*r;
        Split(x,l,r,root);
        Split(x-1,l,m,l);
        m=Merge(m->son[0],m->son[1]);
        root=Merge(Merge(l,m),r);
    }
    int GetRank(int x)
    {
        int now=root->son[0]->siz+1,res=0x3F3F3F3F;
        Node *u=root;
        while(u!=null)
        {
            if(x==u->key)
                res=now;
            if(x<=u->key)
            {
                u=u->son[0];
                now-=u->son[1]->siz+1;
            }
            else
            {
                u=u->son[1];
                now+=u->son[0]->siz+1;
            }
        }
        return res;
    }
    int GetKthNum(int k)
    {
        int now=root->son[0]->siz+1;
        Node *u=root;
        while(u!=null)
        {
            if(k==now)
                return u->key;
            if(k<now)
            {
                u=u->son[0];
                now-=u->son[1]->siz+1;
            }
            else
            {
                u=u->son[1];
                now+=u->son[0]->siz+1;
            }
        }
        return -1;
    }
    int GetPrev(int x)
    {
        int res=-0x3F3F3F3F;
        Node *u=root;
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
    int GetNext(int x)
    {
        int res=0x3F3F3F3F;
        Node *u=root;
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
    while(n--)
    {
        int op,x;
        scanf("%d%d",&op,&x);
        if(op==1)
            Treap::Insert(x);
        else if(op==2)
            Treap::Delete(x);
        else if(op==3)
            printf("%d\n",Treap::GetRank(x));
        else if(op==4)
            printf("%d\n",Treap::GetKthNum(x));
        else if(op==5)
            printf("%d\n",Treap::GetPrev(x));
        else if(op==6)
            printf("%d\n",Treap::GetNext(x));
    }
    return 0;
}
