#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005;

struct Vector
{
    long long x,y;
    Vector(){}
    Vector(long long _x,long long _y):x(_x),y(_y){}

    long long operator ^ (const Vector &t)const
    {return x*t.y-y*t.x;}
    bool operator == (const Vector &t)const
    {return ((*this)^t)==0;}
    bool operator < (const Vector &t)const
    {return ((*this)^t)<0;}
    bool operator <= (const Vector &t)const
    {return ((*this)^t)<=0;}
};

struct Operation
{
    int type;
    int x0,y0,x1,y1;
    int v0,v1,id;
};

class SegmentTree
{
    int vcnt;
    Vector vec[MAXN];
    int val[MAXN*4],id[MAXN*4];

    void Update(pair<int,int> &res,const pair<int,int> &up)
    {
        if(res.first>up.first||(res.first==up.first&&res.second<up.second))
           res=up;
    }

    void Cover(const Vector &l,const Vector &r,int i,int x,int L,int R,int u)
    {
        if(l<=vec[L]&&vec[R]<=r)
        {
            if(val[u]>x||(val[u]==x&&id[u]<i))
                val[u]=x,id[u]=i;
            return;
        }
        int mid=(L+R+1)/2;
        if(l<vec[mid])
            Cover(l,r,i,x,L,mid,u*2);
        if(vec[mid]<r)
            Cover(l,r,i,x,mid,R,u*2+1);
    }
    pair<int,int> Query(const Vector &q,int L,int R,int u)
    {
        pair<int,int> res=make_pair(val[u],id[u]);
        if(R-L<=1)
            return res;
        int mid=(L+R+1)/2;
        if(q<=vec[mid])
            Update(res,Query(q,L,mid,u*2));
        if(vec[mid]<=q)
            Update(res,Query(q,mid,R,u*2+1));
        return res;
    }

public:
    SegmentTree(){vcnt=0;}

    void AddVector(const Vector &v)
    {vec[++vcnt]=v;}
    void Build()
    {
        sort(vec+1,vec+vcnt+1);
        vcnt=unique(vec+1,vec+vcnt+1)-vec-1;
        fill(val,val+MAXN*4,0x3F3F3F3F);
        fill(id,id+MAXN*4,0);
    }
    void Cover(const Vector &l,const Vector &r,int i,int x)
    {Cover(l,r,i,x,1,vcnt,1);}
    pair<int,int> Query(const Vector &q)
    {return Query(q,1,vcnt,1);}
};

int Q,N;
SegmentTree X,Y;
Operation op[MAXN];

int main()
{
    scanf("%d",&Q);
    for(int i=1;i<=Q;i++)
    {
        scanf("%d%d%d",&op[i].type,&op[i].x0,&op[i].y0);
        op[i].id=i;
        if(op[i].type==1)
        {
            scanf("%d%d",&op[i].x1,&op[i].y1);
            X.AddVector(Vector(op[i].x0,op[i].y0));
            X.AddVector(Vector(op[i].x1,op[i].y0));
            Y.AddVector(Vector(op[i].x0,op[i].y1));
            Y.AddVector(Vector(op[i].x0,op[i].y0));
        }
    }
    X.AddVector(Vector(0,0x3F3F3F3F));
    X.AddVector(Vector(0x3F3F3F3F,0));
    Y.AddVector(Vector(0,0x3F3F3F3F));
    Y.AddVector(Vector(0x3F3F3F3F,0));
    X.Build();
    Y.Build();
    for(int i=1;i<=Q;i++)
    {
        if(op[i].type==1)
        {
            if(op[i].y0!=0)
                X.Cover(Vector(op[i].x0,op[i].y0),Vector(op[i].x1,op[i].y0),i,op[i].y0);
            if(op[i].x0!=0)
                Y.Cover(Vector(op[i].x0,op[i].y1),Vector(op[i].x0,op[i].y0),i,op[i].x0);
        }
        else
        {
            Vector q=Vector(op[i].x0,op[i].y0);
            pair<int,int> xres=X.Query(q),yres=Y.Query(q);
            long long tmp=(q^Vector(yres.first,xres.first));
            if(tmp<0||(tmp==0&&xres.second>yres.second))
                printf("%d\n",xres.second);
            else
                printf("%d\n",yres.second);
        }
    }

    return 0;
}
