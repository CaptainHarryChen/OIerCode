#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

int n,m,r[MAXN];
int mn[MAXN*4],delta[MAXN*4];

void Read(int &x)
{
    char c;
    while(c=getchar(),c!=EOF)
    {
        if(c>='0'&&c<='9')
        {
            x=c-'0';
            while(c=getchar(),c>='0'&&c<='9')
                x=x*10+c-'0';
            return;
        }
    }
    return;
}

void Build(int L=1,int R=n,int id=1)
{
    if(L==R)
    {
        mn[id]=r[L];
        delta[id]=0;
        return;
    }
    int mid=(L+R)/2;
    Build(L,mid,id*2);
    Build(mid+1,R,id*2+1);
    mn[id]=min(mn[id*2],mn[id*2+1]);
    delta[id]=0;
}
int Query(int l,int r,int L=1,int R=n,int id=1)
{
    if(l<=L&&R<=r)
        return mn[id];
    int mid=(L+R)/2,res=0x7FFFFFFF;
    mn[id*2]-=delta[id];delta[id*2]+=delta[id];
    mn[id*2+1]-=delta[id];delta[id*2+1]+=delta[id];
    delta[id]=0;
    if(l<=mid)
        res=min(res,Query(l,r,L,mid,id*2));
    if(mid<r)
        res=min(res,Query(l,r,mid+1,R,id*2+1));
    return res;
}
void Subtract(int l,int r,int v,int L=1,int R=n,int id=1)
{
    if(l<=L&&R<=r)
    {
        mn[id]-=v;delta[id]+=v;
        return;
    }
    int mid=(L+R)/2;
    mn[id*2]-=delta[id];delta[id*2]+=delta[id];
    mn[id*2+1]-=delta[id];delta[id*2+1]+=delta[id];
    delta[id]=0;
    if(l<=mid)
        Subtract(l,r,v,L,mid,id*2);
    if(mid<r)
        Subtract(l,r,v,mid+1,R,id*2+1);
    mn[id]=min(mn[id*2],mn[id*2+1]);
}

int main()
{
    Read(n);Read(m);
    for(int i=1;i<=n;i++)
        Read(r[i]);
    Build();
    bool flag=true;
    for(int i=1;i<=m;i++)
    {
        int d,s,t;
        Read(d);Read(s);Read(t);
        if(Query(s,t)<d)
        {
            printf("-1\n%d\n",i);
            flag=false;
            break;
        }
        Subtract(s,t,d);
    }
    if(flag)
        puts("0");

    return 0;
}
