#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MOD=1000000007,MAXN=200005;

long long n,sqr;

bool npr[MAXN];
int pr[MAXN],sum[MAXN],cnt[MAXN],P;
int id1[MAXN],id2[MAXN],m;
long long w[MAXN];
int g[MAXN],h[MAXN];

void LinerSieve()
{
    npr[1]=true;
    for(int i=2;i<=sqr;i++)
    {
        if(!npr[i])
        {
            npr[i]=true;
            pr[++P]=i;
            sum[P]=(sum[P-1]+i)%MOD;
        }
        for(int j=1;j<=P&&1LL*i*pr[j]<MAXN;j++)
        {
            npr[i*pr[j]]=true;
            if(i%pr[j]==0)
                break;
        }
    }
}
void Calc_g_h()
{
    for(long long i=1,j;i<=n;i=j+1)
    {
        j=n/(n/i);
        w[++m]=n/i;
        if(w[m]<=sqr)
            id1[w[m]]=m;
        else
            id2[n/w[m]]=m;
        g[m]=(w[m]%MOD+2)*(w[m]%MOD-1)%MOD*(MOD+1)/2%MOD;
        h[m]=w[m]%MOD-1;
    }
    for(int j=1;j<=P;j++)
        for(int i=1;i<=m&&1LL*pr[j]*pr[j]<=w[i];i++)
        {
            long long k=w[i]/pr[j];
            k=(k<=sqr)?id1[k]:id2[n/k];
            g[i]=(g[i]-1LL*pr[j]*(g[k]-sum[j-1])%MOD+MOD)%MOD;
            h[i]=(h[i]-1LL*(h[k]-(j-1))%MOD+MOD)%MOD;
        }
}
int S(long long x,int j)
{
    if(x<=1||pr[j]>x)
        return 0;
    int k=(x<=sqr)?id1[x]:id2[n/x];
    int res=((g[k]-h[k]-sum[j-1]+(j-1))%MOD+MOD)%MOD;
    if(j==1)
        res=(res+2)%MOD;
    for(int k=j;k<=P&&1LL*pr[k]*pr[k]<=x;k++)
    {
        long long t=pr[k];
        for(int e=1;1LL*pr[k]*t<=x;e++,t*=pr[k])
            res=((res+1LL*(pr[k]^e)*S(x/t,k+1)%MOD)%MOD+(pr[k]^(e+1)))%MOD;
    }
    return res;
}

int main()
{
    scanf("%lld",&n);
    sqr=sqrt(n);
    LinerSieve();
    Calc_g_h();
    int ans=S(n,1)+1;
    printf("%d\n",ans);

    return 0;
}
