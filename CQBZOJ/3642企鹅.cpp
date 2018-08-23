#include<cstdio>
const int MAXN=1005,MOD=2007;

int dp[MAXN][MAXN];

int main()
{
    int n,m;
    for(;;)
    {
        scanf("%d%d",&n,&m);
        if(n==0&&m==0)
            break;
        dp[1][m]=1;
        for(int i=1;i<=n;i++)
            for(int j=i==1?m-1:m;j>=1;j--)
            {
                dp[i][j]=dp[i-1][j];
                if(j<m)
                    dp[i][j]=(dp[i][j]+dp[i][j+1])%MOD;
                //fprintf(stderr,"dp[%d][%d]=%d\n",i,j,dp[i][j]);
            }
        int ans=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                ans=(ans+dp[i][j])%MOD;
        ans-=m-1;
        ans=(ans+MOD)%MOD;
        printf("%d\n",ans);
    }

    return 0;
}
