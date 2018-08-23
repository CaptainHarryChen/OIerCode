#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=16,MAXM=22,MAXS=(1<<14)+10;

int N,M;
int T[MAXN],D[MAXN];
int K[MAXM],E[MAXM],pi[MAXM][MAXN];

int dp[MAXM][MAXS];

int main()
{
    for(;;)
    {
        scanf("%d",&N);
        if(N==0)
            break;
        for(int i=1;i<=N;i++)
            scanf("%d%d",&T[i],&D[i]);
        scanf("%d",&M);
        for(int i=1;i<=M;i++)
        {
            scanf("%d%d",&K[i],&E[i]);
            for(int j=1;j<=K[i];j++)
                scanf("%d",&pi[i][j]);
        }
        int ans=0;
        memset(dp,0x80,sizeof dp);
        dp[0][0]=0;
        for(int i=0;i<=M;i++)
            for(int j=0;j<(1<<N);j++)
                if(dp[i][j]>=0)
                {
                    //printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
                    ans=max(ans,dp[i][j]);
                    for(int k=1;k<=M;k++)
                    {
                        int ts=0,sum=0;
                        bool flag=true;
                        for(int p=1;p<=K[k];p++)
                        {
                            ts|=(1<<(pi[k][p]-1));
                            sum+=T[pi[k][p]]-D[pi[k][p]]*i;
                            if((j&(1<<(pi[k][p]-1)))!=0||T[pi[k][p]]-D[pi[k][p]]*i<0)
                                flag=false;
                        }
                        if(flag)
                            dp[i+1][j|ts]=max(dp[i+1][j|ts],dp[i][j]+sum+E[k]);
                    }
                }
        printf("%d\n",ans);
    }

    return 0;
}
