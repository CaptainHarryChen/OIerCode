#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=88;

int n,a,b,A[MAXN],B[MAXN];
long long dp[MAXN][MAXN][MAXN],best[MAXN][MAXN][MAXN];

int main()
{
    scanf("%d%d%d",&n,&a,&b);
    for(int i=1;i<=a;i++)
        scanf("%d",&A[i]);
    for(int i=1;i<=b;i++)
        scanf("%d",&B[i]);
    sort(A+1,A+a+1);
    sort(B+1,B+b+1);

    memset(dp,0x3F,sizeof dp);
    dp[0][0][0]=0;
    //best[0][0][0]=best[0][0][1]=best[0][1][0]=0;
    for(int i=1;i<=n;i++)
    {
        memset(best[i],0x3F,sizeof best[i]);
        for(int j=1;j<=a;j++)
            for(int k=1;k<=b;k++)
            {
                if(best[i-1][j-1][k-1]<0x3F3F3F3F3F3F3F3FLL)
                    dp[i][j][k]=best[i-1][j-1][k-1]+(A[j]-B[k])*(A[j]-B[k]);
                best[i][j][k]=min(best[i][j-1][k-1],min(dp[i][j][k],min(best[i][j-1][k],best[i][j][k-1])));
                //fprintf(stderr,"dp[%d][%d][%d]=%I64d\n",i,j,k,dp[i][j][k]);
                //fprintf(stderr,"best[%d][%d][%d]=%I64d\n",i,j,k,best[i][j][k]);
            }
    }
    long long ans=0x3F3F3F3F3F3F3F3FLL;
    for(int j=1;j<=a;j++)
        for(int k=1;k<=b;k++)
            ans=min(ans,dp[n][j][k]);
    printf("%lld\n",ans);
    return 0;
}
