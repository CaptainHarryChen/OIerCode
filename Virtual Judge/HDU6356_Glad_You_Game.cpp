#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXM=15000005;

int n,m;
unsigned int X,Y,Z;

unsigned int RNG61()
{
    X=(X^(X<<11));
    X=(X^(X>>4));
    X=(X^(X<<5));
    X=(X^(X>>14));
    unsigned int W=(X^(Y^Z));
    X=Y;
    Y=Z;
    Z=W;
    return Z;
}

unsigned int f[MAXM];
int up[MAXN*4];

void Build(int L=1,int R=n,int id=1)
{
    up[id]=1;
    if(L==R)
        return;
    int mid=(L+R)/2;
    Build(L,mid,id*2);
    Build(mid+1,R,id*2+1);
}
void Modify(int l,int r,int nval,int L=1,int R=n,int id=1)
{
    if(nval<=up[id])
        return;
    if(l<=L&&R<=r)
    {
        up[id]=max(up[id],nval);
        return;
    }
    int mid=(L+R)/2;
    if(l<=mid)
        Modify(l,r,nval,L,mid,id*2);
    if(mid<r)
        Modify(l,r,nval,mid+1,R,id*2+1);
}
long long solve(int val=1,int L=1,int R=n,int id=1)
{
    val=max(val,up[id]);
    if(L==R)
    {
        //printf("[%d]\n",val);
        return 1LL*L*val;
    }
    int mid=(L+R)/2;
    long long ans=0;
    ans^=solve(val,L,mid,id*2);
    ans^=solve(val,mid+1,R,id*2+1);
    return ans;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%u%u%u",&n,&m,&X,&Y,&Z);
        Build();
        for(int i=1;i<=m*3;i++)
            f[i]=RNG61();
        for(int i=1;i<=m;i++)
        {
            unsigned int l,r,v;
            l=min((f[3*i-2]%n)+1,(f[3*i-1]%n)+1);
            r=max((f[3*i-2]%n)+1,(f[3*i-1]%n)+1);
            v=f[3*i]%(1<<30);
            Modify(l,r,v);
            //solve();
            //puts("");
        }
        printf("%I64d\n",solve());
    }
    return 0;
}
