#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const long long MAXN=100005;

long long dp[MAXN];
long long N,M,T,A[MAXN];
long long que[MAXN],hd,tl;
long long stk[MAXN],tp;

void push_back2(long long i)
{
    while(tp>0&&dp[i]-A[i+1]*3<=dp[stk[tp]]-A[stk[tp]+1]*3)
        tp--;
    stk[++tp]=i;
}
void push_back1(long long i)
{
    while(hd<=tl&&dp[i]-A[i+1]<=dp[que[tl]]-A[que[tl]+1])
        tl--;
    que[++tl]=i;
}

int main()
{
    scanf("%lld%lld%lld",&N,&M,&T);
    for(long long i=1;i<=N;i++)
        scanf("%lld",&A[i]);
    A[N+1]=M;
    memset(dp,0x3F,sizeof dp);
    dp[0]=A[1];
    que[1]=0;
    hd=tl=1;
    for(long long i=1;i<=N;i++)
    {
        while(hd<=tl&&(A[i]-A[que[hd]+1])*2>T)
        {
            push_back2(que[hd]);
            hd++;
        }
        if(hd<=tl)
            dp[i]=dp[que[hd]]+T+A[i+1]-A[que[hd]+1];
        if(tp)
            dp[i]=min(dp[i],dp[stk[1]]+A[i]*2+A[i+1]-A[stk[1]+1]*3);
        push_back1(i);
    }
    printf("%lld\n",dp[N]);

    return 0;
}
