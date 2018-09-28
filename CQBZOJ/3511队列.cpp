#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=300005;

int N,M,Q;

int maxrange;
struct Node
{
    int cnt;
    Node *son[2];
}nodes[MAXN*12],*ncnt,*null=nodes;

void Init()
{
    null=nodes;
    ncnt=nodes+1;
    null->cnt=0;
    null->son[0]=null->son[1]=null;
}
Node *NewNode()
{
    ncnt->cnt=0;
    ncnt->son[0]=ncnt->son[1]=null;
    return ncnt++;
}

class SegmentTree
{
    Node *root;
    void Insert(int pos,int L,int R,Node *&now)
    {
        if(now==null)
            now=NewNode();
        now->cnt++;
        if(L==R)
            return;
        int mid=(L+R)/2;
        if(pos<=mid)
            Insert(pos,L,mid,now->son[0]);
        else
            Insert(pos,mid+1,R,now->son[1]);
    }
    int Query(int key,int L,int R,Node *now)
    {
        if(L==R)
            return L;
        int mid=(L+R)/2;
        if(key<=(mid-L+1)-now->son[0]->cnt)
            return Query(key,L,mid,now->son[0]);
        return Query(key-((mid-L+1)-now->son[0]->cnt),mid+1,R,now->son[1]);
    }
public:
    void Init(){root=null;}
    void Insert(int pos)
    {Insert(pos,1,maxrange,root);}
    int Query(int key)
    {return Query(key,1,maxrange,root);}
};

SegmentTree row[MAXN],col;
vector<long long> rG[MAXN],cG;

long long SolveRow(int x,int y)
{
    int pos=row[x].Query(y);
    row[x].Insert(pos);
    if(pos<=M-1)
        return 1LL*(x-1)*M+pos;
    return rG[x][pos-M];
}
long long SolveCol(int x)
{
    int pos=col.Query(x);
    col.Insert(pos);
    if(pos<=N)
        return 1LL*pos*M;
    return cG[pos-N-1];
}

int main()
{
    scanf("%d%d%d",&N,&M,&Q);
    maxrange=Q+max(N,M);
    Init();
    for(int i=1;i<=N;i++)
        row[i].Init();
    col.Init();
    while(Q--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(y!=M)
        {
            long long res=SolveRow(x,y);
            long long tmp=SolveCol(x);
            rG[x].push_back(tmp);
            cG.push_back(res);
            printf("%lld\n",res);
        }
        else
        {
            long long res=SolveCol(x);
            cG.push_back(res);
            printf("%lld\n",res);
        }
    }

    return 0;
}
