#include<cstdio>
const int MAXN=50005;

int main()
{
    int n,A;
    long long sum1=0,sum2=0,ans=0;
    scanf("%d%d",&n,&A);
    for(int i=1;i<=n;i++)
    {
        int t;
        scanf("%d",&t);
        long long tmp=sum1*sum1;
        tmp=(tmp-sum2)/2;
        //ans+=(sum1*sum1-sum2)/2*t
        ans=(ans+1LL*tmp*t%A)%A;
        sum1+=t;
        sum2+=1LL*t*t;
    }
    ans=(ans+A)%A;
    printf("%lld\n",ans);

    return 0;
}
