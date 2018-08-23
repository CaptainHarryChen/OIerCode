#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1005,MAXK=17,MAXS=(1<<8)+5;

template<class T> void Read(T &x)
{
    char c;
    while(c=getchar(),c!=EOF)
    {
        if(c>='0'&&c<='9')
        {
            x=c-'0';
            while(c=getchar(),c>='0'&&c<='9')
                x=x*10+c-'0';
            return;
        }
    }
}

int N,K;
int H[MAXN],cf[MAXN][MAXN];

int len[MAXN];
int dp[MAXN][MAXS][MAXK];

int main()
{
    Read(N);Read(K);
    for(int i=1;i<=N;i++)
        Read(H[i]);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            Read(cf[i][j]);

    len[1]=1;
    for(int i=2;i<=N;i++)
    {
        len[i]=len[i-1]+1;
        while(H[i]-H[i-len[i]+1]>=K)
            len[i]--;
    }

    memset(dp,0x3F,sizeof dp);
    dp[1][1][0]=0;
    for(int i=1;i<=N;i++)
        for(int s=0;s<(1<<len[i]);s++)
            for(int k=0;k<MAXK&&k<i;k++)
                if(dp[i][s][k]<0x3F3F3F3F)
                {
                    for(int p=0;p<len[i];p++)
                        if((s&(1<<p))==0)
                        {
                            int ts=s|(1<<p);
                            dp[i][ts][p]=min(dp[i][ts][p],dp[i][s][k]+cf[i-k][i-p]);
                        }
                    if(len[i]==len[i+1]-1||(s>>(len[i+1]-1))==(1<<(len[i]-len[i+1]+1))-1)
                    {
                        if(dp[i][s][k]==66)
                            i++,i--;
                        if(i==9&&s==240)
                            i++,i--;
                        int ts=(s<<1)&((1<<len[i+1])-1);
                        dp[i+1][ts][k+1]=min(dp[i+1][ts][k+1],dp[i][s][k]);
                    }
                }
    int ans=0x3F3F3F3F;
    for(int k=0;k<len[N];k++)
        ans=min(ans,dp[N][(1<<len[N])-1][k]);
    printf("%d\n",ans);

    return 0;
}
