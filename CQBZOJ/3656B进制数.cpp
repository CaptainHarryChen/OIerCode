#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

int B,q;
int a[MAXN];
long long pos[MAXN];

int main()
{
    scanf("%d%d",&B,&q);
    long long sum=0;
    for(int i=0;i<B;i++)
    {
        scanf("%d",&a[i]);
        sum=(sum+(1LL*a[i]*i)%(B-1))%(B-1);
    }
    if(sum!=0)
        a[sum]--;
    pos[0]=a[0]-1;
    for(int i=1;i<B;i++)
        pos[i]=pos[i-1]+a[i];
    while(q--)
    {
        long long k;
        scanf("%lld",&k);
        int ans=lower_bound(pos,pos+B,k)-pos;
        if(ans>=B)
            puts("-1");
        else
            printf("%d\n",ans);
    }
    return 0;
}
