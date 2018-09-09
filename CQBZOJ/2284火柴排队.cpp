#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MOD=99999997;

int sum[MAXN];
int Get(int p)
{
    int res=0;
    while(p>0)
    {
        res+=sum[p];
        p-=(p&(-p));
    }
    return res;
}
void Add(int p,int val)
{
    while(p<MAXN)
    {
        sum[p]+=val;
        p+=(p&(-p));
    }
}

int n,A[MAXN],B[MAXN],C[MAXN],D[MAXN],P[MAXN],Q[MAXN];
int m,mp[MAXN*2];
int posA[MAXN*2],posB[MAXN*2];
bool vis[MAXN];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&A[i]),mp[i]=A[i];
    for(int i=1;i<=n;i++)
        scanf("%d",&B[i]),mp[i+n]=B[i];
    sort(mp+1,mp+2*n+1);
    m=unique(mp+1,mp+2*n+1)-mp-1;
    for(int i=1;i<=n;i++)
    {
        C[i]=A[i]=lower_bound(mp+1,mp+m+1,A[i])-mp;
        D[i]=B[i]=lower_bound(mp+1,mp+m+1,B[i])-mp;
        posA[A[i]]=i;
        posB[B[i]]=i;
    }
    sort(C+1,C+n+1);
    sort(D+1,D+n+1);
    for(int i=1;i<=n;i++)
        P[posA[C[i]]]=posB[D[i]];
    for(int i=1;i<=n;i++)
        Q[P[i]]=i;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int x=Q[i]+Get(Q[i]);
        ans=(ans+x-i)%MOD;
        Add(1,1);
        Add(Q[i]+1,-1);
    }
    printf("%d\n",ans);
    
    return 0;
}
