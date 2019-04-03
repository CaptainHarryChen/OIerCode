#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const long long MAXN=1000005,MAXK=22;
const long long TEST_LIST[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47},TEST_NUM=15;

long long p10[MAXK],p5[MAXK],p2[MAXK];
void Init()
{
    p10[0]=p5[0]=p2[0]=1;
    for(long long i=1;i<MAXK;i++)
    {
        p10[i]=p10[i-1]*10;
        p5[i]=p5[i-1]*5;
        p2[i]=p2[i-1]*2;
    }
}
long long lg10(long long x)
{
    for(long long i=0;i<19;i++)
        if(p10[i]>x)
            return i;
    return 19;
}
long long MulMod(long long a,long long b,long long p)
{return (a*b-((long long)floor((long double)a/p*b)*p)+p)%p;}
/*{
    long long res=0;
    for(;b;b>>=1,a=(a+a)%p)
        if(b&1)
            res=(res+a)%p;
    return res;
}*/
long long PowMod(long long a,long long b,long long p)
{
    long long res=1;
    for(;b;b>>=1,a=MulMod(a,a,p))
        if(b&1)
            res=MulMod(res,a,p);
    return res;
}
bool MillarRabin(long long a,long long n,long long x,long long k)
{
    long long y=PowMod(a,x,n);
    if(y==n-1||y==1)
        return true;
    while(k--)
    {
        y=MulMod(y,y,n);
        if(y==n-1)
            return true;
        if(y==1&&k!=0)
            return false;
    }
    return false;
}
bool isPrime(long long x)
{
    if(x==2||x==3||x==5||x==7)
        return true;
    if(x<=10)
        return false;
    long long y=x-1;
    long long k=0;
    while(y%2==0)
        y/=2,k++;
    for(long long i=0;i<TEST_NUM;i++)
        if(x%TEST_LIST[i]!=0&&!MillarRabin(TEST_LIST[i],x,y,k))
            return false;
    return true;
}
long long gcd(long long a,long long b)
{return b==0?a:gcd(b,a%b);}
long long PollarRho(long long d,long long n)
{
    if(n%2==0)
        return 2;
    long long a=1,b=1,g;
    for(;;)
    {
        a=(MulMod(a,a,n)+d)%n;
        b=(MulMod(b,b,n)+d)%n;
        b=(MulMod(b,b,n)+d)%n;
        if(a==b)
            return 1;
        g=gcd(a>b?a-b:b-a,n);
        if(g!=1&&g!=n)
            return g;
    }
    return 1;
}
void Factorize(long long n,vector<long long> &res)
{
    if(n==1)return;
    if(isPrime(n))
    {
        res.push_back(n);
        return;
    }
    long long p=1;
    for(long long i=1;p==1||p==n;i++)
        p=PollarRho(i,n);
    Factorize(p,res);
    Factorize(n/p,res);
}

long long n,ans;
vector<long long> tmp;
long long fac[MAXN];
long long cnt[MAXN],tot;
long long a,b,k1,k2;
void dfs(long long step,long long d)
{
    if(d*a>n||d*b>n)
        return;
    if(step>tot)
    {
        long long A=d*a,B=d*b;
        if(lg10(B)==k2&&lg10(1LL*A*B)==k1)
            ans++;
        return;
    }
    for(long long i=0;i<=cnt[step];i++)
    {
        dfs(step+1,d);
        d*=fac[step];
    }
}
void Find_d()
{
    long long m=p10[k1+k2]/b+p10[k1]/a;
    tmp.clear();
    Factorize(m,tmp);
    sort(tmp.begin(),tmp.end());
    tot=0;
    for(long long i=0;i<(long long)tmp.size();i++)
        if(i==0||tmp[i]!=tmp[i-1])
            fac[++tot]=tmp[i],cnt[tot]=1;
        else
            cnt[tot]++;
    dfs(1,1);
}

int main()
{
    scanf("%lld",&n);
    Init();
    long long l1=lg10(n),l2=lg10(n*n);
    for(k1=1;k1<=l2;k1++)
        for(k2=1;k2<=l1&&k2<=k1;k2++)
        {
            for(long long a2=0;a2<=k1;a2++)
                for(long long a5=0;a5<=k1;a5++)
                    for(long long b2=0;b2<=(a2==0)*(k1+k2);b2++)
                        for(long long b5=0;b5<=(a5==0)*(k1+k2);b5++)
                        {
                            a=p2[a2]*p5[a5];b=p2[b2]*p5[b5];
                            if(a>n||b>n)
                                continue;
                            //printf("(%lld %lld %lld %lld)",k1,k2,a,b);
                            Find_d();
                            //printf("=%lld\n",ans);
                        }
        }

    printf("%lld\n",ans);
    return 0;
}
