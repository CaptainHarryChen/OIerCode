#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int SEED[]={2,3,5,7,11,13,17,19,23,29,31},SEED_NUM=11;

long long MulMod(long long a,long long b,long long p)
{
    a%=p;b%=p;
    long long res=0;
    while(b)
    {
        if(b&1)
            res=(res+a)%p;
        a=(a+a)%p;
        b>>=1;
    }
    return res;
}
long long PowMod(long long a,long long b,long long p)
{
    a%=p;
    long long res=1;
    while(b)
    {
        if(b&1)
            res=MulMod(res,a,p);
        a=MulMod(a,a,p);
        b>>=1;
    }
    return res;
}

bool MillarRabin(long long a,long long x,long long r,long long k)
{
    a=PowMod(a,r,x);
    if(a==1||a==x-1)
        return true;
    while(k)
    {
        a=MulMod(a,a,x);
        k--;
        if(a==1)
            return false;
        if(a==x-1)
            return true;
    }
    return false;
}
bool IsPrime(long long x)
{
    if(x<=10)
        return x==2||x==3||x==5||x==7;
    long long r=x-1,k=0;
    while((r&1)==0)
        r>>=1,k++;
    for(int t=0;t<SEED_NUM&&SEED[t]<x;t++)
        if(!MillarRabin(SEED[t],x,r,k))
            return false;
    return true;
}

long long gcd(long long x,long long y)
{return y==0?x:gcd(y,x%y);}
long long PollardRho(long long x)
{
    if((x&1)==0)
        return 2;
    for(;;)
    {
        long long t=rand()%(x-1)+1,a=1,b=1;
        for(;;)
        {
            a=(MulMod(a,a,x)+t)%x;
            b=(MulMod(b,b,x)+t)%x;
            b=(MulMod(b,b,x)+t)%x;
            if(a==b)
                break;
            long long g=gcd(a>b?a-b:b-a,x);
            if(g!=1)
                return g;
        }
    }
}
long long MinFactor(long long x)
{
    if(IsPrime(x))
        return x;
    long long p;
    do
        p=PollardRho(x);
    while(p==x||p==1);
    return min(MinFactor(x/p),MinFactor(p));
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        long long x;
        scanf("%lld",&x);
        if(IsPrime(x))
            puts("Prime");
        else
            printf("%lld\n",MinFactor(x));
    }
    return 0;
}
