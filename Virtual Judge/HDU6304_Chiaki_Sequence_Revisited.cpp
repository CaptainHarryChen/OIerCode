#include<cstdio>
const int MAXN=1000006,MOD=1000000007,INV2=(MOD+1)/2;

long long f(long long x)
{
    long long a=1,ret=0,i=1;
    while(a<=x)
    {
        ret+=((x-a)/(a*2LL)+1)*i;
        a<<=1LL;
        i++;
    }
    ret++;
    return ret;
}
long long getNval(long long n)
{
    long long L=(n+1)/2LL,R=L+64,mid;
    while(L<R)
    {
        mid=(L+R)/2;
        long long res=f(mid);
        if(res<n)
            L=mid+1;
        else
            R=mid;
    }
    return L;
}
long long getSum(long long a1,long long d,long long n)
{
    //sum=d/2*n*n+(a1+d/2)*n
    d%=MOD;
    d=d*INV2%MOD;
    n%=MOD;
    a1%=MOD;
    return (d*n%MOD*n%MOD+(a1-d+MOD)%MOD*n%MOD)%MOD;
}
long long getAns(long long n,long long an)
{
    long long a1=1,d=2,t=1,i=1;
    long long ret=0;
    while(t<an)
    {
        ret=(ret+getSum(a1,d,(an-1-t)/(t<<1LL)+1)*i%MOD)%MOD;
        t<<=1LL;i++;d<<=1LL;a1<<=1LL;
    }
    ret++;
    long long hjb=f(an-1);
    ret+=(n-hjb)%MOD*an%MOD;
    ret%=MOD;
    return ret;
}

int main()
{
    int T;
    long long n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%I64d",&n);
        long long an=getNval(n);
        long long sum=getAns(n,an);
        printf("%I64d\n",sum);
    }
    return 0;
}
