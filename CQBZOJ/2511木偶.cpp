#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=305;

int n;
int A[MAXN],cnt[MAXN];
int dp[MAXN][MAXN];

int main()
{
    while(~scanf("%d",&n))
    {
        memset(cnt,0,sizeof cnt);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&A[i]);
            cnt[A[i]]++;
        }
        memset(dp,0x80,sizeof dp);
        dp[0][0]=0;
        dp[1][cnt[1]]=0;
        for(int i=2;i<=100;i++)
            for(int j=0;j<=cnt[i];j++)
            {
                for(int k=0;k<=cnt[i-1];k++)
                    dp[i][j]=max(dp[i][j],dp[i-1][k]);
                for(int k=0;k<=cnt[i-2];k++)
                    dp[i][j]=max(dp[i][j],dp[i-2][k]+min(k,min(cnt[i-1],cnt[i]-j)));
            }
        int ans=0;
        for(int i=0;i<=n;i++)
            ans=max(ans,dp[100][i]);
        printf("%d\n",ans);
    }
    return 0;
}
