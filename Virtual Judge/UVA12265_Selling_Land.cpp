#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1005;

int n,m;
char mp[MAXN][MAXN];

int h[MAXN][MAXN],best[MAXN][MAXN];
pair<int,int> stk[MAXN];
int tp;
int cnt[MAXN*6];

int main()
{
    //freopen("data.in","r",stdin);
    //freopen("data.out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
        {
            scanf("%s",mp[i]+1);
            for(int j=1;j<=m;j++)
                if(mp[i][j]=='#')
                    h[i][j]=0;
                else
                    h[i][j]=h[i-1][j]+1;
        }

        for(int i=1;i<=n;i++)
        {
            tp=0;
            for(int j=1;j<=m;j++)
            {
                if(mp[i][j]=='#')
                {
                    best[i][j]=0;
                    tp=0;
                    continue;
                }
                int k=j;
                while(tp>0&&stk[tp].first>=h[i][j])
                    k=stk[tp].second,tp--;
                if(tp==0||h[i][j]-k>stk[tp].first-stk[tp].second)
                    stk[++tp]=make_pair(h[i][j],k);
                best[i][j]=(stk[tp].first+j-stk[tp].second+1)*2;
            }
        }
        /*for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                printf("%3d%c",best[i][j]," \n"[j==m]);*/
        memset(cnt,0,sizeof cnt);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(best[i][j])
                    cnt[best[i][j]]++;
        for(int i=1;i<=(n+m)*2;i++)
            if(cnt[i])
                printf("%d x %d\n",cnt[i],i);
    }
    return 0;
}
