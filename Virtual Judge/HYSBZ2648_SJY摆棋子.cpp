#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500005;

struct Point
{
    int p[2];
};

struct Node
{
    Point P,mx,mn;
    Node *ch[2];

    void Update()
    {
        mx=mn=P;
        if(ch[0])
        {
            mx.p[0]=max(mx.p[0],ch[0]->mx.p[0]);
            mx.p[1]=max(mx.p[1],ch[0]->mx.p[1]);
            mn.p[0]=min(mn.p[0],ch[0]->mn.p[0]);
            mn.p[1]=min(mn.p[1],ch[0]->mn.p[1]);
        }
        if(ch[1])
        {
            mx.p[0]=max(mx.p[0],ch[1]->mx.p[0]);
            mx.p[1]=max(mx.p[1],ch[1]->mx.p[1]);
            mn.p[0]=min(mn.p[0],ch[1]->mn.p[0]);
            mn.p[1]=min(mn.p[1],ch[1]->mn.p[1]);
        }
    }
    int dis(Point Q)
    {
        int res=0;
        if(Q.p[0]<mn.p[0])
            res+=mn.p[0]-Q.p[0];
        if(Q.p[0]>mx.p[0])
            res+=Q.p[0]-mx.p[0];
        if(Q.p[1]<mn.p[1])
            res+=mn.p[1]-Q.p[1];
        if(Q.p[1]>mx.p[1])
            res+=Q.p[1]-mx.p[1];
        return res;
    }

}nodes[MAXN*8],*root,*n_it=nodes;

int N,M,D,ans;
Point piece[MAXN];

bool cmp(Point a,Point b)
{return a.p[D]<b.p[D];}

void Build(int L,int R,Node *&u=root,int d=0)
{
    if(L>R)
        return;
    u=n_it++;
    int mid=(L+R)/2;
    D=d;
    nth_element(piece+L,piece+mid,piece+R+1,cmp);
    u->P=piece[mid];
    Build(L,mid-1,u->ch[0],d^1);
    Build(mid+1,R,u->ch[1],d^1);
    u->Update();
}

void Insert(Point Q,Node *&u=root,int d=0)
{
    if(u==NULL)
    {
        u=n_it++;
        u->P=Q;
        u->Update();
        return;
    }
    if(Q.p[d]<=u->P.p[d])
        Insert(Q,u->ch[0],d^1);
    else
        Insert(Q,u->ch[1],d^1);
    u->Update();
}

void Query(Point Q,Node *u=root,int d=0)
{
    if(abs(u->P.p[0]-Q.p[0])+abs(u->P.p[1]-Q.p[1])<ans)
        ans=abs(u->P.p[0]-Q.p[0])+abs(u->P.p[1]-Q.p[1]);
    int dl,dr;
    if(u->ch[0])
        dl=u->ch[0]->dis(Q);
    else
        dl=0x3F3F3F3F;
    if(u->ch[1])
        dr=u->ch[1]->dis(Q);
    else
        dr=0x3F3F3F3F;
    if(dl<dr)
    {
        if(dl<ans)
            Query(Q,u->ch[0],d^1);
        if(dr<ans)
            Query(Q,u->ch[1],d^1);
    }
    else
    {
        if(dr<ans)
            Query(Q,u->ch[1],d^1);
        if(dl<ans)
            Query(Q,u->ch[0],d^1);
    }
}

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;i++)
        scanf("%d%d",&piece[i].p[0],&piece[i].p[1]);
    Build(1,N);
    for(int i=1;i<=M;i++)
    {
        int t;
        Point Q;
        scanf("%d%d%d",&t,&Q.p[0],&Q.p[1]);
        if(t==1)
            Insert(Q);
        else
        {
            ans=0x3F3F3F3F;
            Query(Q);
            printf("%d\n",ans);
        }
    }

    return 0;
}
