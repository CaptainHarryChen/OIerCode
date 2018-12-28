#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=5005,MAXL=20005,MINY=-10000,MAXY=10000;

struct Segment
{
    int x;
    int y1,y2;
    int type;

    Segment(){}
    Segment(int _x,int _y1,int _y2,int _type)
    {x=_x;y1=_y1;y2=_y2;type=_type;}
    bool operator < (const Segment &t)const
    {return x<t.x||(x==t.x&&type>t.type);}
};

struct Rect
{
    int x1,y1,x2,y2;
};

int n,m;
Rect re[MAXN];
Segment seg[MAXN*2];

int ans;

int cov[MAXL*4],len[MAXL*4];

void Build(int L=MINY,int R=MAXY,int id=1)
{
    cov[id]=0;
    len[id]=0;
    if(R-L<=1)
        return;
    int mid=(L+R)>>1;
    Build(L,mid,id<<1);
    Build(mid,R,id<<1);
}
void Update(int id,int L,int R)
{
    if(cov[id])
        len[id]=R-L;
    else
    {
        if(R-L<=1)
            len[id]=0;
        else
            len[id]=len[id<<1]+len[id<<1|1];
    }
}
void Add(int l,int r,int val,int L=MINY,int R=MAXY,int id=1)
{
    if(l<=L&&R<=r)
    {
        cov[id]+=val;
        Update(id,L,R);
        return;
    }
    int mid=(L+R)>>1;
    if(l<mid)
        Add(l,r,val,L,mid,id<<1);
    if(mid<r)
        Add(l,r,val,mid,R,id<<1|1);
    Update(id,L,R);
}

int Solve()
{
    Build();
    int Len=0,res=0;
    for(int i=1;i<=m;i++)
    {
        Add(seg[i].y1,seg[i].y2,seg[i].type);
        res+=abs(Len-len[1]);
        Len=len[1];
    }
    return res;
}

int main()
{
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;i++)
            scanf("%d%d%d%d",&re[i].x1,&re[i].y1,&re[i].x2,&re[i].y2);

        ans=0;

        m=0;
        for(int i=1;i<=n;i++)
        {
            seg[++m]=Segment(re[i].x1,re[i].y1,re[i].y2,1);
            seg[++m]=Segment(re[i].x2,re[i].y1,re[i].y2,-1);
        }
        sort(seg+1,seg+m+1);
        ans+=Solve();

        m=0;
        for(int i=1;i<=n;i++)
        {
            seg[++m]=Segment(re[i].y1,re[i].x1,re[i].x2,1);
            seg[++m]=Segment(re[i].y2,re[i].x1,re[i].x2,-1);
        }
        sort(seg+1,seg+m+1);
        ans+=Solve();

        printf("%d\n",ans);
    }

    return 0;
}
