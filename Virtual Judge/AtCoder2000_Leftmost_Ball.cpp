#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=2005,MOD=1000000007;

int PowMod(int a,int b)
{
    int ret=1;
    while(b)
    {
        if(b&1)
            ret=1LL*ret*a%MOD;
        a=1LL*a*a%MOD;
        b>>=1;
    }
    return ret;
}

int fac[MAXN*MAXN],ifac[MAXN*MAXN];

void Init()
{
    fac[0]=1;
    for(int i=1;i<MAXN*MAXN;i++)
        fac[i]=1LL*fac[i-1]*i%MOD;
    ifac[MAXN*MAXN-1]=PowMod(fac[MAXN*MAXN-1],MOD-2);
    for(int i=MAXN*MAXN-2;i>=0;i--)
        ifac[i]=1LL*ifac[i+1]*(i+1)%MOD;
}
int C(int n,int r)
{return 1LL*fac[n]*ifac[n-r]%MOD*ifac[r]%MOD;}

int N,K,dp[MAXN][MAXN];

int main()
{
    Init();
    scanf("%d%d",&N,&K);
    if(K==1)
    {
        puts("1");
        return 0;
    }
    dp[0][0]=1;
    for(int i=0;i<=N;i++)
        for(int j=0;j<=i;j++)
        {
            if(i)
                dp[i][j]=(dp[i][j]+dp[i-1][j])%MOD;
            if(j)
                dp[i][j]=(dp[i][j]+1LL*dp[i][j-1]*C(N*K-i-(K-1)*(j-1)-1,K-2)%MOD)%MOD;
        }
    int ans=1LL*dp[N][N]*fac[N]%MOD;
    printf("%d\n",ans);

    return 0;
}
