#include<cstdio>
#include<cstring>
const int MAXN=12;

int n,m,lim;
char mp[MAXN][MAXN];
int used[4][MAXN*2];

bool check()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(mp[i][j]=='X'&&!used[0][i]&&!used[1][j]&&!used[2][n-i+j]&&!used[3][i+j-1])
                return false;
    return true;
}

bool dfs(int step,int lastr=1,int lastj=1)
{
    if(step>lim)
    {
        if(check())
            return true;
        return false;
    }
    for(int r=lastr;r<=n;r++)
        for(int j=lastj;j<=m;j++)
        {
            used[0][r]++;used[1][j]++;used[2][n-r+j]++;used[3][r+j-1]++;
            if(dfs(step+1,r+1,1))
                return true;
            used[0][r]--;used[1][j]--;used[2][n-r+j]--;used[3][r+j-1]--;
        }
    return false;
}

int main()
{
    for(int test=1;scanf("%d%d",&n,&m)==2;test++)
    {
        for(int i=1;i<=n;i++)
            scanf("%s",mp[i]+1);
        int ans=5;
        memset(used,0,sizeof used);
        for(lim=0;lim<=5;lim++)
            if(dfs(1))
            {
                ans=lim;
                break;
            }
        printf("Case %d: %d\n",test,ans);
    }
    return 0;
}
