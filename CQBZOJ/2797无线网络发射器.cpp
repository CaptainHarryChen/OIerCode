#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=25,MAXM=128;

int n,d;
int x[MAXN],y[MAXN],k[MAXN];

int main()
{
    scanf("%d%d",&d,&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&x[i],&y[i],&k[i]);
    int ans1=0,ans2=0;
    for(int X=0;X<=MAXM;X++)
        for(int Y=0;Y<=MAXM;Y++)
        {
            int cnt=0;
            for(int i=1;i<=n;i++)
                if(abs(X-x[i])<=d&&abs(Y-y[i])<=d)
                    cnt+=k[i];
            if(cnt==ans1)
                ans2++;
            if(cnt>ans1)
            {
                ans1=cnt;
                ans2=1;
            }
        }
    printf("%d %d\n",ans2,ans1);
    return 0;
}
