#include<cstdio>
const int MAXN=105,MOD=2007;

int PowMod(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1)
            res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

int C[MAXN][MAXN];
void InitC()
{
    C[0][0]=1;
    for(int i=1;i<MAXN;i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
    }
}

int main()
{
    InitC();
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        int ans=0;
        for(int i=0;i<n;i++)
            (ans+=C[n][i]*PowMod(4,i)%MOD*(n-i)%MOD*4%MOD)%=MOD;
        printf("%d\n",ans);
    }

    return 0;
}
