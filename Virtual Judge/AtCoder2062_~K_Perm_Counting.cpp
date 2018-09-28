#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=4005,MOD=924844033;

int C[MAXN][MAXN],dp[MAXN][MAXN][2];
int len[MAXN];
bool ed[MAXN];
vector<int> chain;
int fac[MAXN];
void Init()
{
    C[0][0]=1;
    for(int i=1;i<MAXN;i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
    }
    fac[0]=1;
    for(int i=1;i<MAXN;i++)
        fac[i]=1LL*fac[i-1]*i%MOD;
}

int main()
{
    Init();
    int N,K;
    scanf("%d%d",&N,&K);

    for(int i=1;i<=N;i++)
    {
        len[i]=(i-K>0)+(i+K<=N);
        ed[i]=true;
        if(i>2*K)
            len[i]+=len[i-2*K],ed[i-2*K]=false;
    }
    for(int i=1;i<=N;i++)
        if(ed[i]&&len[i])
            chain.push_back(len[i]);
    dp[0][0][0]=1;
    int mx;
    for(int i=1,j=-1,k=1;j<(int)chain.size();i++,k++)
    {
        if(j==-1||k>chain[j])
        {
            j++,k=1;
            if(j>=(int)chain.size())
                break;
            for(int p=1;p<=i;p++)
                dp[i][p][1]=(dp[i-1][p-1][0]+dp[i-1][p-1][1])%MOD;
        }
        else
        {
            for(int p=1;p<=i;p++)
                dp[i][p][1]=dp[i-1][p-1][0];
        }
        for(int p=0;p<=i;p++)
            dp[i][p][0]=(dp[i-1][p][0]+dp[i-1][p][1])%MOD;
        mx=i;
    }

    int ans=fac[N];
    for(int i=1,f0=-1;i<=N;i++,f0=-f0)
    {
        int tmp=0;
        tmp=(tmp+(dp[mx][i][0]+dp[mx][i][1])%MOD)%MOD;
        tmp=(tmp+MOD)%MOD;
        tmp=1LL*tmp*fac[N-i]%MOD;
        ans=(ans+f0*tmp)%MOD;
    }
    ans=(ans+MOD)%MOD;
    printf("%d\n",ans);

    return 0;
}