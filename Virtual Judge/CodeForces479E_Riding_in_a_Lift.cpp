#include<cstdio>
const int MAXN=5005,MOD=1000000007;

int n,a,b,K;
int dp[MAXN][MAXN],sum[MAXN][MAXN];

int main()
{
    scanf("%d%d%d%d",&n,&a,&b,&K);

    dp[0][a]=1;
    for(int j=a;j<=n;j++)
        sum[0][j]=(sum[0][j-1]+dp[0][j])%MOD;
    for(int i=1;i<=K;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(j<b)
                dp[i][j]=(dp[i][j]+sum[i-1][j+(b-j-1)/2]-dp[i-1][j])%MOD;
            if(j>b)
                dp[i][j]=(((((dp[i][j]+sum[i-1][n])%MOD-sum[i-1][j-(j-b-1)/2-1])+MOD)%MOD-dp[i-1][j])%MOD+MOD)%MOD;
            //printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
        }
        for(int j=1;j<=n;j++)
            sum[i][j]=(sum[i][j-1]+dp[i][j])%MOD;
    }
    printf("%d\n",(sum[K][n]+MOD)%MOD);


    return 0;
}
