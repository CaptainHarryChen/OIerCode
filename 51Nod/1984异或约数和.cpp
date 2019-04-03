#include<cstdio>

long long Sum(long long x)
{
    if(x%4==0)
        return x;
    if(x%4==1)
        return 1;
    if(x%4==2)
        return x+1;
    return 0;
}

int main()
{
    long long n,sum=0;
    scanf("%lld",&n);
    for(long long i=1,nxt;i<=n;i=nxt+1)
    {
        nxt=n/(n/i);
        if((n/i)&1)
            sum^=Sum(nxt)^Sum(i-1);
    }
    printf("%lld\n",sum);
    return 0;
}
