#include<cstdio>
#include<algorithm>
using namespace std;

long long ans=-1,ta,tb,tc;
void check(int n,int a,int b)
{
    int c=n-a-b;
    if(c>0&&n%c==0)
        if(ans<1LL*a*b*c)
        {
            ans=max(ans,1LL*a*b*c);
            ta=a;tb=b;tc=c;
        }
}

int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--)
    //freopen("test.out","w",stdout);
    //for(int n=1;n<=1000000;n++)
    {
        scanf("%d",&n);
        if(n%3==0)
        {
            printf("%I64d\n",1LL*(n/3)*(n/3)*(n/3));
        }
        else if(n%4==0)
        {
            printf("%I64d\n",1LL*(n/2)*(n/4)*(n/4));
        }
        else
            puts("-1");
        ans=-1;
        /*for(int i=1;i*i<=n;i++)
            if(n%i==0)
                for(int j=1;j*j<=n;j++)
                    if(n%j==0)
                    {
                        check(n,i,j);
                        check(n,i,n/j);
                        check(n,n/i,j);
                        check(n,n/i,n/j);
                    }*/
        //printf("%I64d\n",ans);
        //printf("(%I64d,%I64d,%I64d)\n",ta,tb,tc);
    }
    return 0;
}
