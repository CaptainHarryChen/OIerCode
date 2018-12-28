#include<cstdio>
const int MAXN=1000005,MOD=1000000007;

int PowMod(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1)
            res=1LL*res*a%MOD;
        a=1LL*a*a%MOD;
        b>>=1;
    }
    return res;
}

int fac[MAXN],ifac[MAXN];
int sum[MAXN];

int main()
{
    fac[0]=1;
    for(int i=1;i<MAXN;i++)
        fac[i]=1LL*fac[i-1]*i%MOD;
    ifac[MAXN-1]=PowMod(fac[MAXN-1],MOD-2);
    for(int i=MAXN-2;i>=0;i--)
        ifac[i]=1LL*ifac[i+1]*(i+1)%MOD;

    sum[0]=1;
    for(int i=1,flag=-1;i<MAXN;i++,flag=-flag)
        sum[i]=((sum[i-1]+flag*ifac[i])%MOD+MOD)%MOD;

    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        printf("%d\n",(int)(1LL*fac[n]*ifac[m]%MOD*ifac[n-m]%MOD*fac[n-m]%MOD*sum[n-m]%MOD));
    }

    return 0;
}
