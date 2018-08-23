#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1005,MAXS=1030,MAXM=20;

int T,n,m,k;
int cnt[MAXS],A[MAXN];
char str[MAXN][MAXM];

int main()
{
    scanf("%d",&T);
    for(int test=1;test<=T;test++)
    {
        scanf("%d%d%d",&n,&m,&k);
        memset(A,0,sizeof A);
        int tmp,ans=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%s",str[i]);
            for(int j=0;j<m;j++)
                if(str[i][j]=='B')
                    A[i]|=(1<<j);
        }
        for(int s=1;s<(1<<m);s++)
        {
            memset(cnt,0,sizeof cnt);
            for(int i=1;i<=n;i++)
                cnt[A[i]&s]++;
            tmp=0;
            for(int ts=0;ts<(1<<m);ts++)
                tmp+=cnt[ts]*(n-cnt[ts]);
            tmp/=2;
            if(tmp>=k)
                ans++;
        }
        printf("Case #%d: %d\n",test,ans);
    }
    
    return 0;
}