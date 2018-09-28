#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int segsiz;
int mn[MAXN*4];

int Query(int pos,int L=1,int R=segsiz,int id=1)
{
    if(L==R)
        return mn[id];
    int ret=mn[id],mid=(L+R)/2;
    if(pos<=mid)
        return min(ret,Query(pos,L,mid,id*2));
    return min(ret,Query(pos,mid+1,R,id*2+1));
}
void Insert(int l,int r,int v,int L=1,int R=segsiz,int id=1)
{
    if(l>r)
        return;
    if(l<=L&&R<=r)
    {
        mn[id]=min(mn[id],v);
        return;
    }
    int mid=(L+R)/2;
    if(l<=mid)
        Insert(l,r,v,L,mid,id*2);
    if(mid<r)
        Insert(l,r,v,mid+1,R,id*2+1);
}

int N,M,K,A[MAXN],B[MAXN];
int sumA[MAXN];
int L[MAXN],R[MAXN];
int val[MAXN];
long long dp[MAXN];

int main()
{
    scanf("%d%d",&N,&K);
    long long sum=0;
    for(int i=1;i<=N;i++)
    {
        scanf("%d%d",&A[i],&B[i]);
        if(B[i]==1&&2*A[i]>K)
        {
            puts("-1");
            return 0;
        }
        sum+=A[i];
        sumA[i]=(sumA[i-1]+A[i])%K;
    }
    for(int i=1;i<=N;i++)
    {
        if(B[i]==1)
        {
            L[i]=2*(K-sumA[i-1])%K;
            R[i]=2*(K-sumA[i])%K;
        }
        else
            L[i]=0,R[i]=K-1;
    }
    for(int i=1;i<=N;i++)
        val[i*2-1]=L[i],val[i*2]=R[i];
    sort(val+1,val+2*N+1);
    M=unique(val+1,val+2*N+1)-val-1;
    for(int i=1;i<=N;i++)
    {
        L[i]=lower_bound(val+1,val+M+1,L[i])-val;
        R[i]=lower_bound(val+1,val+M+1,R[i])-val;
    }
    segsiz=M;
    memset(mn,0x3F,sizeof mn);
    for(int i=N;i>=1;i--)
    {
        int j=Query(L[i]);
        if(j==0x3F3F3F3F)
            dp[i]=0;
        else
            dp[i]=dp[j]+(val[L[j]]-val[L[i]]+K)%K;
        if(L[i]<=R[i])
        {
            Insert(1,L[i]-1,i);
            Insert(R[i]+1,M,i);
        }
        else
            Insert(R[i]+1,L[i]-1,i);
    }
    long long ans=0x3F3F3F3F3F3F3F3FLL;
    for(int i=1;i<=M;i++)
    {
        int j=Query(i);
        if(j==0x3F3F3F3F)
            ans=0;
        else
            ans=min(ans,1LL*(val[L[j]]-val[i]+K)%K+dp[j]);
    }
    ans=ans+2LL*sum;
    printf("%lld\n",ans);

    return 0;
}
