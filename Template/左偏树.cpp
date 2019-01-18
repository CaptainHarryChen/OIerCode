//luogu P3377
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005;

namespace LeftishTree
{
    struct Node *null;
    struct Node
    {
        int key,id,dis;
        Node *son[2];
    };
    Node tree[MAXN],*nd_it;
    Node *NewNode(int k,int i)
    {
        nd_it->key=k;
        nd_it->id=i;
        nd_it->dis=1;
        nd_it->son[0]=nd_it->son[1]=null;
        return nd_it++;
    }
    void Init()
    {
        null=tree;
        null->son[0]=null->son[1]=null;
        null->dis=null->key=0;
        nd_it=tree+1;
    }

    Node *Merge(Node *A,Node *B)
    {
        if(A==null)
            return B;
        if(B==null)
            return A;
        if(make_pair(A->key,A->id)>make_pair(B->key,B->id))
            swap(A,B);
        A->son[1]=Merge(A->son[1],B);
        A->dis=min(A->son[0]->dis,A->son[1]->dis)+1;
        if(A->son[1]->dis>A->son[0]->dis)
            swap(A->son[0],A->son[1]);
        return A;
    }
    void Delete(Node *&A)
    {
        A=Merge(A->son[0],A->son[1]);
    }
}
namespace DSU
{
    int fa[MAXN];
    int Root(int x)
    {return fa[x]==0?x:(fa[x]=Root(fa[x]));}
    void Merge(int x,int y)
    {
        int r1=Root(x),r2=Root(y);
        if(r1==r2)
            return;
        fa[r2]=r1;
    }
}

int N,M;
LeftishTree::Node *nd[MAXN];
bool del[MAXN];

int main()
{
    LeftishTree::Init();
    scanf("%d%d",&N,&M);
    for(int i=1,v;i<=N;i++)
    {
        scanf("%d",&v);
        nd[i]=LeftishTree::NewNode(v,i);
    }
    for(int i=1;i<=M;i++)
    {
        int op,x,y;
        scanf("%d",&op);
        if(op==1)
        {
            scanf("%d%d",&x,&y);
            if(!del[x]&&!del[y])
            {
                x=DSU::Root(x);y=DSU::Root(y);
                if(x!=y)
                {
                    nd[x]=LeftishTree::Merge(nd[x],nd[y]);
                    DSU::Merge(x,y);
                }
            }
        }
        else
        {
            scanf("%d",&x);
            if(del[x])
                puts("-1");
            else
            {
                x=DSU::Root(x);
                printf("%d\n",nd[x]->key);
                del[nd[x]->id]=true;
                LeftishTree::Delete(nd[x]);
            }
        }
    }

    return 0;
}
