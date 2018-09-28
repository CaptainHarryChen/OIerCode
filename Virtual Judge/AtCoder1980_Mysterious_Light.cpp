#include<cstdio>
#include<algorithm>
using namespace std;

long long solve(long long a,long long b)
{
    if(a==0)
        return 0;
    long long res=a*(b/a)*2;
    if(b%a==0)
    {
        res-=a;
        return res;
    }
    return res+solve(b%a,a);
}

int main()
{
    long long N,X;
    scanf("%lld%lld",&N,&X);
    long long ans=N+solve(min(X,N-X),max(X,N-X));
    printf("%lld\n",ans);

    return 0;
}
