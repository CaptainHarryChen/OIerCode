#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int N,M,Q;

struct Edge
{
    int u,v;
}E[MAXN];
struct Query
{
    int x,y,z;
}q[MAXN];
int id[MAXN],tmp[MAXN],mk[MAXN],ans[MAXN];

int stk[MAXN][2],tp;
int fa[MAXN],siz[MAXN];
int Root(int u)
{
    if(fa[u]==0)
        return u;
    return Root(fa[u]);
}
void Union(int u,int v)
{
    int r1=Root(u),r2=Root(v);
    if(r1==r2)
        return;
    if(siz[r1]<siz[r2])
        swap(r1,r2);
    fa[r2]=r1;
    stk[++tp][0]=r2;
    stk[tp][1]=r1;
    siz[r1]+=siz[r2];
}

void solve(int a,int b,int l,int r)
{
    if(a==b)
    {
        for(int i=l;i<=r;i++)
            ans[id[i]]=a;
        Union(E[a].u,E[a].v);
        return;
    }
    tp=0;
    int mid1=(a+b)/2;
    for(int i=a;i<=mid1;i++)
        Union(E[i].u,E[i].v);
    for(int i=l;i<=r;i++)
    {
        int r1=Root(q[id[i]].x),r2=Root(q[id[i]].y);
        if(r1==r2&&siz[r1]>=q[id[i]].z)
            mk[i]=1;
        if(r1!=r2&&siz[r1]+siz[r2]>=q[id[i]].z)
            mk[i]=1;
    }
    int it=l-1;
    for(int i=l;i<=r;i++)
        if(mk[i])
            tmp[++it]=id[i];
    int mid2=it;
    for(int i=l;i<=r;i++)
        if(!mk[i])
            tmp[++it]=id[i];
    for(int i=l;i<=r;i++)
        id[i]=tmp[i],mk[i]=0;
    while(tp)
    {
        fa[stk[tp][0]]=0;
        siz[stk[tp][1]]-=siz[stk[tp][0]];
        tp--;
    }
    solve(a,mid1,l,mid2);
    solve(mid1+1,b,mid2+1,r);
}

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;i++)
        scanf("%d%d",&E[i].u,&E[i].v);
    scanf("%d",&Q);
    for(int i=1;i<=Q;i++)
        scanf("%d%d%d",&q[i].x,&q[i].y,&q[i].z);
    for(int i=1;i<=N;i++)
        fa[i]=0,siz[i]=1;
    for(int i=1;i<=Q;i++)
        id[i]=i;
    solve(1,M,1,Q);
    for(int i=1;i<=Q;i++)
        printf("%d\n",ans[i]);

    return 0;
}
