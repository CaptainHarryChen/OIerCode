#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=305;

int n,A[MAXN];
int ans[2*MAXN*MAXN],tp;

int main()
{
    for(;;)
    {
        scanf("%d",&n);
        if(n==0)
            break;
        for(int i=1;i<=n;i++)
            scanf("%d",&A[i]);
        tp=0;
        for(;;)
        {
            bool flag=true;
            for(int i=1;i<=n;i++)
                if(A[i]!=i)
                {
                    flag=false;
                    break;
                }
            if(flag)
                break;
            if(A[1]>A[2]&&A[2]!=1)
            {
                ans[++tp]=1;
                swap(A[1],A[2]);
            }
            else
            {
                ans[++tp]=2;
                int t=A[n];
                for(int i=n;i>=2;i--)
                    A[i]=A[i-1];
                A[1]=t;
            }
        }
        for(int i=tp;i>0;i--)
            printf("%d",ans[i]);
        puts("");
    }
    return 0;
}
