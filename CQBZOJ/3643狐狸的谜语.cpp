#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=35,MAXT=305;

int dp[MAXN][MAXT][MAXT];
char s[MAXN];
int T,N;

int GetNum(int a,int b)
{
    int ret=0;
    for(int i=a;i<=b;i++)
        ret=(ret*10+s[i]-'0');
    return ret;
}

int main()
{
    for(;;)
    {
        scanf("%s%d",s+1,&T);
        if(T<0)
            break;
        N=strlen(s+1);
        memset(dp,0x3F,sizeof dp);
        for(int i=1;i<=N;i++)
        {
            int num=GetNum(1,i);
            if(num>T)
                break;
            dp[i][0][num]=0;
        }
        for(int i=1;i<=N;i++)
            if(s[i]=='0')
                dp[i][0][0]=min(dp[i][0][0],1);
        for(int i=1;i<N;i++)
            for(int j=0;j<=T;j++)
                for(int k=0;k+j<=T;k++)
                    if(dp[i][j][k]<N)
                    {
                        if(k==0)
                            for(int p=i+1;p<=N;p++)
                                dp[p][j][0]=min(dp[p][j][0],dp[i][j][k]+1);
                        for(int p=i+1;p<=N;p++)
                        {
                            int num=GetNum(i+1,p);
                            if(num>T)
                                break;
                            if(k*num<=T)
                                dp[p][j][k*num]=min(dp[p][j][k*num],dp[i][j][k]+1);
                            if(num<=T)
                                dp[p][j+k][num]=min(dp[p][j+k][num],dp[i][j][k]+1);
                        }
                        for(int p=i+1;p<=N;p++)
                            if(s[p]=='0')
                            {
                                dp[p][j+k][0]=min(dp[p][j+k][0],dp[i][j][k]+2);
                                dp[p][j][0]=min(dp[p][j][0],dp[i][j][k]+2);
                            }
                    }
        int ans=0x3F3F3F3F;
        for(int j=0;j<=T;j++)
            ans=min(ans,dp[N][j][T-j]);
        if(ans==0x3F3F3F3F)
            ans=-1;
        printf("%d\n",ans);
    }
    return 0;
}
