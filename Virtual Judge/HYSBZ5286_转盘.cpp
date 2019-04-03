#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int n,m,p;
int t[MAXN],a[MAXN];

int mx[MAXN*4],val[MAXN*4];
int Query(int L,int R,int u,int p)
{
    if(L==R)
        return L+max(mx[u],p);
    int mid=(L+R)/2;
    if(mx[u*2+1]>=p)
        return min(val[u],Query(mid+1,R,u*2+1,p));
    return min(mid+1+p,Query(L,mid,u*2,p));
}
void PushUp(int L,int mid,int u)
{
    val[u]=Query(L,mid,u*2,mx[u*2+1]);
    mx[u]=max(mx[u*2],mx[u*2+1]);
}
void Build(int L=1,int R=n*2,int u=1)
{
    if(L==R)
    {
        mx[u]=a[L];
        val[u]=a[L]+L;
        return;
    }
    int mid=(L+R)/2;
    Build(L,mid,u*2);
    Build(mid+1,R,u*2+1);
    PushUp(L,mid,u);
}
void Modify(int p,int L=1,int R=n*2,int u=1)
{
    if(L==R)
    {
        mx[u]=a[L];
        val[u]=a[L];
        return;
    }
    int mid=(L+R)/2;
    if(p<=mid)
        Modify(p,L,mid,u*2);
    else
        Modify(p,mid+1,R,u*2+1);
    PushUp(L,mid,u);
}

int main()
{
    scanf("%d%d%d",&n,&m,&p);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&t[i]);
        a[i]=t[i]-i;
        a[i+n]=t[i]-i-n;
    }
    Build();
    int last=val[1]+n-1;
    printf("%d\n",last);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(p)
            x^=last,y^=last;
        a[x]=y-x;
        a[x+n]=y-x-n;
        Modify(x);
        Modify(x+n);
        last=val[1]+n-1;
        printf("%d\n",last);
    }

    return 0;
}
