#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXK=10000005,MAXN=305,MAXW=300*300+10,MOD=1000000007;

inline int PowMod(int a,int b)
{
    int res=1;
    for(;b;b>>=1,a=1LL*a*a%MOD)
        if(b&1)
            res=1LL*res*a%MOD;
    return res;
}

int n,m,k,w[MAXN];
int dp[MAXN][MAXW],sum[MAXN][MAXW];

int fac[MAXK],ifac[MAXK];
inline int C(int a,int b)
{return 1LL*fac[a]*ifac[a-b]%MOD*ifac[b]%MOD;}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(register int i=1;i<=m;i++)
        scanf("%d",&w[i]);
    dp[0][0]=1;
    for(int j=0;j<=k&&j<MAXW;j++)
        sum[0][j]=1;
    for(register int i=1;i<=m;i++)
        for(register int j=0;j<=k&&j<MAXW;j++)
        {
            dp[i][j]=sum[i-1][j];
            if(j-w[i]-1>=0)
                dp[i][j]-=sum[i-1][j-w[i]-1];
            if(dp[i][j]<0)
                dp[i][j]+=MOD;
            if(j)
                sum[i][j]=sum[i][j-1]+dp[i][j];
            else
                sum[i][j]=dp[i][j];
            if(sum[i][j]>=MOD)
                sum[i][j]-=MOD;
        }

    fac[0]=1;
    for(register int i=1;i<=k+n;i++)
        fac[i]=1LL*fac[i-1]*i%MOD;
    ifac[k+n]=PowMod(fac[k+n],MOD-2);
    for(register int i=k+n-1;i>=0;i--)
        ifac[i]=1LL*ifac[i+1]*(i+1)%MOD;

    int ans=0;
	if(n==m)
		ans=dp[m][k];
	else
		for(register int j=0;j<=k&&j<MAXW;j++)
			ans=(ans+1LL*dp[m][j]*C(n-m-1+k-j,n-m-1)%MOD)%MOD;
    printf("%d\n",ans);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
