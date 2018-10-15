#include<cstdio>
const int MAXN=1000005,MOD=1000000007;

inline int PowMod(int a,int b)
{
    register int ret=1;
    while(b)
    {
        if(b&1)
            ret=1LL*a*ret%MOD;
        b>>=1;
        a=1LL*a*a%MOD;
    }
    return ret;
}
inline int Inv(int a)
{return PowMod(a,MOD-2);}

int N;
int cnt[MAXN];

bool npr[MAXN];
int prime[MAXN],pcnt;

void LinerSieve()
{
    npr[1]=1;
    for(int i=2;i<=N;i++)
    {
        if(!npr[i])
            prime[++pcnt]=i;
        for(int j=1;j<=pcnt&&prime[j]*i<=N;j++)
        {
            npr[prime[j]*i]=true;
            if(i%prime[j]==0)
                break;
        }
    }
}

int main()
{
    scanf("%d",&N);
    LinerSieve();
    for(int i=1;i<=pcnt;i++)
        for(long long j=prime[i];j<=N;j*=prime[i])
            cnt[prime[i]]+=N/j;
    int x=1;
    for(register int i=1;i<=N;i++)
        x=1LL*x*i%MOD;
    for(register int i=2;i<=N;i++)
        if(cnt[i])
            x=1LL*x*(i-1)%MOD*Inv(i)%MOD;
    int y=1;
    for(register int i=2;i<=N;i++)
        y=1LL*y*(cnt[i]+1)%MOD;
    int ans=1;
    for(register int i=1;i<=N;i++)
        ans=1LL*ans*i%MOD;
    ans=ans-x-y+1;
    ans=(ans%MOD+MOD)%MOD;
    printf("%d\n",ans);

    return 0;
}
