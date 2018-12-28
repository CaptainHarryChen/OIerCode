#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=500005;

struct Point
{
    static int key;

    int p[2];
    int &operator [] (int i)
    {return p[i];}
    const int &operator [] (int i)const
    {return p[i];}
    bool operator < (const Point &t)const
    {return p[key]<t[key];}
};

int dis(const Point &A,const Point &B)
{return abs(A[0]-B[0])+abs(A[1]-B[1]);}

struct Node
{
    Point A,mn,mx;
    Node *ch[2];

    void Update()
    {
        mn=mx=A;
        for(int i=0;i<2;i++)
            if(ch[i])
                for(int j=0;j<2;j++)
                {
                    mn[j]=min(mn[j],ch[i]->mn[j]);
                    mx[j]=max(mx[j],ch[i]->mx[j]);
                }
    }
    int dis(const Point &B)
    {
        int res=0;
        if(B[0]<mn[0])
            res+=mn[0]-B[0];
        if(B[1]<mn[1])
            res+=mn[1]-B[1];
        if(B[0]>mx[0])
            res+=B[0]-mx[0];
        if(B[1]>mx[1])
            res+=B[1]-mx[1];
        return res;
    }
    int disfar(const Point &B)
    {return max(abs(B[0]-mx[0]),abs(B[0]-mn[0]))+max(abs(B[1]-mx[1]),abs(B[1]-mn[1]));}
};

int N,Point::key;
Point P[MAXN];

Node nodes[MAXN],*root,*n_it=nodes;

void Build(int L=1,int R=N,Node *&u=root,int d=0)
{
    if(L>R)
        return;
    u=n_it++;
    int mid=(L+R)/2;
    Point::key=d;
    nth_element(P+L,P+mid,P+R+1);
    u->A=P[mid];
    Build(L,mid-1,u->ch[0],d^1);
    Build(mid+1,R,u->ch[1],d^1);
    u->Update();
}

int far,near;

void QueryFarthest(const Point &Q,Node *u=root)
{
    if(u==NULL)
        return;
    if(far<dis(Q,u->A))
        far=dis(Q,u->A);
    int dl=-0x3F3F3F3F,dr=-0x3F3F3F3F;
    if(u->ch[0])
        dl=u->ch[0]->disfar(Q);
    if(u->ch[1])
        dr=u->ch[1]->disfar(Q);
    if(dl>dr)
    {
        if(dl>far)
            QueryFarthest(Q,u->ch[0]);
        if(dr>far)
            QueryFarthest(Q,u->ch[1]);
    }
    else
    {
        if(dr>far)
            QueryFarthest(Q,u->ch[1]);
        if(dl>far)
            QueryFarthest(Q,u->ch[0]);
    }
}

void QueryNearest(const Point &Q,Node *u=root)
{
    if(u==NULL)
        return;
    if(dis(Q,u->A)>0&&near>dis(Q,u->A))
        near=dis(Q,u->A);
    int dl=0x3F3F3F3F,dr=0x3F3F3F3F;
    if(u->ch[0])
        dl=u->ch[0]->dis(Q);
    if(u->ch[1])
        dr=u->ch[1]->dis(Q);
    if(dl<dr)
    {
        if(dl<near)
            QueryNearest(Q,u->ch[0]);
        if(dr<near)
            QueryNearest(Q,u->ch[1]);
    }
    else
    {
        if(dr<near)
            QueryNearest(Q,u->ch[1]);
        if(dl<near)
            QueryNearest(Q,u->ch[0]);
    }
}

int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
        scanf("%d%d",&P[i][0],&P[i][1]);

    Build();
    int ans=0x3F3F3F3F;
    for(int i=1;i<=N;i++)
    {
        far=-0x3F3F3F3F;
        QueryFarthest(P[i]);
        near=0x3F3F3F3F;
        QueryNearest(P[i]);
        ans=min(ans,far-near);
    }
    printf("%d\n",ans);

    return 0;
}
