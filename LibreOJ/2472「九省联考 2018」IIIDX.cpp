#include<cmath>
#include<cstdio>
#include<cstring>
#include<functional>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=500005;

int n,d[MAXN],siz[MAXN],ans[MAXN];
vector<int> adj[MAXN];
double k;

void GetSize(int u)
{
    siz[u]=1;
    for(int i=0;i<(int)adj[u].size();i++)
    {
        GetSize(adj[u][i]);
        siz[u]+=siz[adj[u][i]];
    }
}

int mn[MAXN*4],tag[MAXN*4];
void PushUp(int u)
{
    mn[u]=min(mn[u*2],mn[u*2+1]);
}
void PushDown(int u)
{
    mn[u*2]+=tag[u];
    mn[u*2+1]+=tag[u];
    tag[u*2]+=tag[u];
    tag[u*2+1]+=tag[u];
    tag[u]=0;
}
void Build(int L=1,int R=n,int u=1)
{
    if(L==R)
    {
        mn[u]=L;
        return;
    }
    int mid=(L+R)/2;
    Build(L,mid,u*2);
    Build(mid+1,R,u*2+1);
    PushUp(u);
}
void Update(int l,int r,int x,int L=1,int R=n,int u=1)
{
    if(l<=L&&R<=r)
    {
        mn[u]+=x;
        tag[u]+=x;
        return;
    }
    PushDown(u);
    int mid=(L+R)/2;
    if(l<=mid)
        Update(l,r,x,L,mid,u*2);
    if(mid<r)
        Update(l,r,x,mid+1,R,u*2+1);
    PushUp(u);
}
int Query(int x,int L=1,int R=n,int u=1)
{
    if(L==R)
        return mn[u]>=x?L:L+1;
    PushDown(u);
    int mid=(L+R)/2;
    if(mn[u*2+1]>=x)
        return Query(x,L,mid,u*2);
    return Query(x,mid+1,R,u*2+1);
}

int pos[MAXN],be[MAXN],cnt_be;

int main()
{
    scanf("%d%lf",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&d[i]);
    sort(d+1,d+n+1,greater<int>());
    for(int i=1;i<=n+1;i++)
        if(d[i]!=d[i-1])
            pos[cnt_be]=i-1,be[i]=++cnt_be;
        else
            be[i]=cnt_be;
    for(int i=1;i<=n;i++)
        adj[(int)floor(i/k)].push_back(i);
    GetSize(0);
    Build();
    for(int i=1;i<=n;i++)
    {
        int f=(int)floor(i/k);
        if(f)
            Update(ans[f],n,siz[i]);
        int p=Query(siz[i]);
        p=pos[be[p]];
        pos[be[p]]--;
        Update(p,n,-siz[i]);
        ans[i]=p;
    }
    for(int i=1;i<=n;i++)
        printf("%d%c",d[ans[i]]," \n"[i==n]);

    return 0;
}
