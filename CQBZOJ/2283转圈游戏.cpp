#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int PowMod(int a,int b,int p)
{
    int res=1;
    while(b)
    {
        if(b&1)
            res=1LL*res*a%p;
        a=1LL*a*a%p;
        b>>=1;
    }
    return res;
}

int main()
{
    int n,m,k,x,ans;
    scanf("%d%d%d%d",&n,&m,&k,&x);
    ans=(1LL*m*PowMod(10,k,n)%n+x)%n;
    printf("%d\n",ans);

    return 0;
}
