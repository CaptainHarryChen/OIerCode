#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=10005,MAXM=1005;

int n,m,k;
int dp[MAXN][MAXM],best[MAXN][MAXM];
int X[MAXN],Y[MAXN];
int L[MAXN],H[MAXN];

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&X[i],&Y[i]);
    for(int i=1;i<=k;i++)
    {
        int pos,l,h;
        scanf("%d%d%d",&pos,&l,&h);
        L[pos]=l;
        H[pos]=h;
    }
    memset(dp,0x3F,sizeof dp);
    memset(best,0x3F,sizeof best);
    for(int j=1;j<=m;j++)
    {
        dp[0][j]=0;
        best[0][min(j+X[1],m)]=min(best[0][min(j+X[1],m)],dp[0][j]+1);
    }
    int cnt=0;
    bool flag=false;
    for(int i=1;i<=n;i++)
    {
        flag=false;
        int l=L[i],r=H[i];
        if(l==0&&r==0)
            l=0,r=m+1;
        else
            cnt++;
        l++,r--;
        for(int j=l;j<=r;j++)
        {
            if(j+Y[i]<=m)
                dp[i][j]=min(dp[i][j],dp[i-1][j+Y[i]]);
            dp[i][j]=min(dp[i][j],best[i-1][j]);
            best[i][min(j+X[i+1],m)]=min(best[i][min(j+X[i+1],m)],dp[i][j]+1);
            if(dp[i][j]<0x3F3F3F3F)
                flag=true;
        }
        for(int j=1;j<=m;j++)
            best[i][min(j+X[i+1],m)]=min(best[i][min(j+X[i+1],m)],best[i][j]+1);
        if(!flag)
        {
            if(L[i]!=0||H[i]!=0)
                cnt--;
            printf("0\n%d\n",cnt);
            break;
        }
    }

    if(flag)
    {
        int ans=0x3F3F3F3F;
        for(int j=1;j<=m;j++)
            ans=min(ans,dp[n][j]);
        printf("1\n%d\n",ans);
    }
    return 0;
}
