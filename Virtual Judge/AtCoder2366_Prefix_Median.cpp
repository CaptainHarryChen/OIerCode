#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=55,MOD=1000000007;

int N,A[MAXN*2];
int dp[MAXN][MAXN*2][MAXN*2];

int main()
{
    scanf("%d",&N);
    for(int i=1;i<=2*N-1;i++)
        scanf("%d",&A[i]);
    sort(A+1,A+2*N);

    dp[N][1][0]=1;
    for(int i=N-1;i>=1;i--)
    {
        int al=(A[i]!=A[i+1]),ar=(A[2*N-i]!=A[2*N-i-1]);
        for(int l=0;l<=2*N-1;l++)
            for(int r=0;l+r<=2*N-1;r++)
                if(dp[i+1][l][r])
                {
                    for(int k=1;k<=l+al;k++)
                        (dp[i][l+al-k+1][r+ar+(k!=1)]+=dp[i+1][l][r])%=MOD;
                    for(int k=1;k<=r+ar;k++)
                        (dp[i][l+al+1][r+ar-k]+=dp[i+1][l][r])%=MOD;
                }
    }

    int ans=0;
    for(int l=0;l<=2*N-1;l++)
        for(int r=0;l+r<=2*N-1;r++)
            (ans+=dp[1][l][r])%=MOD;
    printf("%d\n",ans);

    return 0;
}
