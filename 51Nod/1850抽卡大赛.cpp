#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=205,MOD=1000000007;

int PowMod(int a,int b)
{
    int res=1;
    for(;b;b>>=1,a=1LL*a*a%MOD)
        if(b&1)
            res=1LL*res*a%MOD;
    return res;
}

struct Node
{
    int A,x,y;
    bool operator < (const Node &t)const
    {return A<t.A;}
};
struct Card
{
    int A,G,P;
    bool operator < (const Card &t)const
    {return A<t.A;}
};

int n,m,M[MAXN],V[MAXN],inv100;
Card A[MAXN][MAXN];
int sum[MAXN][MAXN],Q[MAXN];
int ans[MAXN],dp[MAXN],pos[MAXN];
Node cd[MAXN*MAXN];

void Del(int p)
{
    int p1=PowMod((1-p+MOD)%MOD,MOD-2);
    dp[0]=1LL*dp[0]*p1%MOD;
    for(int j=1;j<n;j++)
        dp[j]=1LL*(dp[j]-1LL*dp[j-1]*p%MOD+MOD)%MOD*p1%MOD;
}
void Add(int p)
{
    int p1=(1-p+MOD)%MOD;
    for(int j=n-1;j>=1;j--)
        dp[j]=(1LL*dp[j-1]*p%MOD+1LL*dp[j]*p1%MOD)%MOD;
    dp[0]=1LL*dp[0]*p1%MOD;
}

int main()
{
    inv100=PowMod(100,MOD-2);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&M[i]);
        for(int j=1;j<=M[i];j++)
            scanf("%d%d%d",&A[i][j].A,&A[i][j].G,&A[i][j].P);
        sort(A[i]+1,A[i]+M[i]+1);
        for(int j=1;j<=M[i];j++)
        {
            sum[i][j]=(sum[i][j-1]+A[i][j].P)%MOD;
            m++;
            cd[m].A=A[i][j].A;
            cd[m].x=i;
            cd[m].y=j;
        }
        Q[i]=PowMod(sum[i][M[i]],MOD-2);
    }
    sort(cd+1,cd+m+1);
    for(int i=1;i<=n;i++)
        scanf("%d",&V[i]);
    dp[0]=1;
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
            if(j!=cd[i].x)
            {
                int last=pos[j];
                while(pos[j]<M[j]&&A[j][pos[j]+1].A<cd[i].A)
                    pos[j]++;
                if(last!=pos[j])
                {
                    if(last!=0)
                        Del(1LL*sum[j][last]*Q[j]%MOD);
                    Add(1LL*sum[j][pos[j]]*Q[j]%MOD);
                }
            }
        if(pos[cd[i].x]!=0)
            Del(1LL*sum[cd[i].x][pos[cd[i].x]]*Q[cd[i].x]%MOD);
        for(int k=0;k<n;k++)
        {
            int val=1LL*V[n-k]*(100-A[cd[i].x][cd[i].y].G)%MOD*inv100%MOD;
            int pro=1LL*A[cd[i].x][cd[i].y].P*Q[cd[i].x]%MOD*dp[k]%MOD;
            ans[cd[i].x]=(ans[cd[i].x]+1LL*val*pro%MOD)%MOD;
        }
        if(pos[cd[i].x]!=0)
            Add(1LL*sum[cd[i].x][pos[cd[i].x]]*Q[cd[i].x]%MOD);
    }
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[i]);

    return 0;
}
