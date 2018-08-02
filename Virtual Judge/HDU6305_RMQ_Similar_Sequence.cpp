#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000006,MOD=1000000007;

long long powmod(long long a,long long b)
{
    long long ret=1;
    for(;b>0;b>>=1,a=(a*a)%MOD)
        if(b&1)
            ret=(ret*a)%MOD;
    return ret;
}
long long inv(long long a)
{return powmod(a,MOD-2);}

int n,h[MAXN];
int l[MAXN],r[MAXN];
int stk[MAXN],tp;

int main()
{
    long long ans;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        if(n==0)
            break;
        for(int i=1;i<=n;i++)
            scanf("%d",h+i);
        l[1]=1;
        stk[1]=1;tp=1;
        for(int i=2;i<=n;i++)
        {
            while(tp>0&&h[stk[tp]]<h[i])
                tp--;
            l[i]=tp==0?1:stk[tp]+1;
            stk[++tp]=i;
        }
        r[n]=n;
        stk[1]=n;tp=1;
        for(int i=n-1;i>=1;i--)
        {
            while(tp>0&&h[stk[tp]]<=h[i])
                tp--;
            r[i]=tp==0?n:stk[tp]-1;
            stk[++tp]=i;
        }
        
        ans=(1LL*n*inv(2))%MOD;
        for(int i=1;i<=n;i++)
            ans=(1LL*ans*inv(r[i]-l[i]+1))%MOD;
        printf("%I64d\n",ans);
    }
    return 0;
}
