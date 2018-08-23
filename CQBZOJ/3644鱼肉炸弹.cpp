#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXK=7,MAXLOG=20;

long long dp[MAXN][MAXK];
int N,K,ncnt;
int H[MAXN],C[MAXN];

int mx[MAXN][MAXLOG],mxid[MAXN][MAXLOG],lg[MAXN];
int GetMax(int L,int R)
{
    int l=lg[R-L+1];
    if(mx[L][l]>mx[R-(1<<l)+1][l])
        return mxid[L][l];
    return mxid[R-(1<<l)+1][l];
}

int dfs(int L,int R)
{
    ncnt++;
    int id=ncnt;
    if(L==R)
    {
        dp[id][0]=C[L];
        for(int i=1;i<=K;i++)
            dp[id][i]=0;
        return id;
    }
    int mid=GetMax(L,R),lch=0,rch=0;
    if(mid!=L)
        lch=dfs(L,mid-1);
    if(mid!=R)
        rch=dfs(mid+1,R);
    dp[id][0]=max(dp[lch][0],dp[rch][0])+C[mid];
    for(int k=1;k<=K;k++)
    {
        dp[id][k]=0x3F3F3F3F3F3F3F3FLL;
        for(int k2=0;k2<=k;k2++)
        {
            dp[id][k]=min(dp[id][k],max(dp[lch][k2],dp[rch][k-k2])+C[mid]);
            if(k2<k)
                dp[id][k]=min(dp[id][k],max(dp[lch][k2],dp[rch][k-k2-1]));
        }
    }
    return id;
}

int main()
{
    scanf("%d%d",&N,&K);
    for(int i=1;i<=N;i++)
        scanf("%d%d",&H[i],&C[i]);

    for(int i=1;i<=N;i++)
        mx[i][0]=H[i],mxid[i][0]=i;
    for(int j=1;(1<<j)<=N;j++)
        for(int i=1;i+(1<<j)-1<=N;i++)
        {
            if(mx[i][j-1]>mx[i+(1<<(j-1))][j-1])
                mx[i][j]=mx[i][j-1],mxid[i][j]=mxid[i][j-1];
            else
                mx[i][j]=mx[i+(1<<(j-1))][j-1],mxid[i][j]=mxid[i+(1<<(j-1))][j-1];
        }
    lg[1]=0;
    for(int i=2;i<=N;i++)
    {
        lg[i]=lg[i-1];
        if((1<<(lg[i]+1))==i)
            lg[i]++;
    }

    dfs(1,N);
    printf("%lld\n",dp[1][K]);

    return 0;
}
