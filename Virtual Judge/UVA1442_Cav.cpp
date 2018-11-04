#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

int T,n,c[MAXN],f[MAXN],h1[MAXN],h2[MAXN];

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&f[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&c[i]);
        int lev=0x3F3F3F3F;
        for(int i=1;i<=n;i++)
        {
            lev=min(lev,c[i]);
            lev=max(lev,f[i]);
            h1[i]=lev;
        }
        lev=0x3F3F3F3F;
        for(int i=n;i>=1;i--)
        {
            lev=min(lev,c[i]);
            lev=max(lev,f[i]);
            h2[i]=lev;
        }
        long long ans=0;
        for(int i=1;i<=n;i++)
            ans+=min(h1[i],h2[i])-f[i];
        printf("%lld\n",ans);
    }
    return 0;
}
