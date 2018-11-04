#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
const int dir[4][2]={{1,0},{0,1},{0,-1},{-1,0}};
const char id[5]="ensw";

bool wall[400][400],vis[400][400];
int cnt,n,k;
int ans[400][22];

void dfs(int x,int y,int step)
{
    int h=0;
    if((n-step+1)&1)
        h=(n+step)*(n-step+2)/4;
    else
        h=(n+step+1)*(n-step+1)/4;
    if(h<abs(x)||h<abs(y))
        return;
    h=(n+step)*(n-step+1)/2;
    if(h<abs(x)+abs(y))
        return;
    if(step>n)
    {
        for(int i=1;i<=n;i++)
            printf("%c",id[ans[cnt][i]]);
        puts("");
        memcpy(ans[cnt+1],ans[cnt],sizeof ans[cnt]);
        cnt++;
        return;
    }
    for(int d=0;d<4;d++)
    {
        if(step>1&&((dir[ans[cnt][step-1]][0]+dir[d][0])%2==0||(dir[ans[cnt][step-1]][1]+dir[d][1])%2==0))
            continue;
        bool flag=true;
        int tx=x,ty=y;
        for(int i=1;i<=step;i++)
        {
            tx+=dir[d][0];ty+=dir[d][1];
            if(wall[tx+200][ty+200])
            {
                flag=false;
                break;
            }
        }
        if(!flag)
            continue;
        if(vis[tx+200][ty+200])
            continue;
        ans[cnt][step]=d;
        vis[tx+200][ty+200]=true;
        dfs(tx,ty,step+1);
        vis[tx+200][ty+200]=false;
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        memset(wall,0,sizeof wall);
        for(int i=1;i<=k;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            wall[x+200][y+200]=true;
        }
        cnt=1;
        dfs(0,0,1);
        cnt--;
        printf("Found %d golygon(s).\n\n",cnt);
    }
    return 0;
}
