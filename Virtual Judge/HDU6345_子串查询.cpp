#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXLOG=20,MAXCHAR=26;

int T,n,q;
char A[MAXN],Min[MAXN][MAXLOG];
int cnt[MAXN][MAXCHAR];

int main()
{
    scanf("%d",&T);
    for(int test=1;test<=T;test++)
    {
        scanf("%d%d%s",&n,&q,A+1);
        memset(cnt,0,sizeof cnt);
        for(int i=1;i<=n;i++)
        {
            Min[i][0]=A[i];
            for(int j=0;j<MAXCHAR;j++)
                cnt[i][j]+=cnt[i-1][j];
            cnt[i][A[i]-'A']++;
        }
        for(int j=1;(1<<j)<=n;j++)
            for(int i=1;i+(1<<j)-1<=n;i++)
                Min[i][j]=min(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);
        printf("Case #%d:\n",test);
        while(q--)
        {
            int l,r,c,lg=0;
            scanf("%d%d",&l,&r);
            while(l+(1<<(lg+1))-1<=r)
                lg++;
            c=min(Min[l][lg],Min[r-(1<<lg)+1][lg])-'A';
            printf("%d\n",cnt[r][c]-cnt[l-1][c]);
        }
    }
    
    return 0;
}