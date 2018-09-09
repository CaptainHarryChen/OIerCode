#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int N=5,M=7,MAXN=8;

int lim,cnt;
int col[N+3][M+3];
int ans[MAXN][3];
int id;
pair<int,int> Q[2][N*M+20],del[N*M+20];
int qtp[2],dtp;

void Update(int tmp[N+3][M+3],int x,int y)
{
    int cnt=0,l,r;
    for(l=x;l>0&&tmp[l][y]==tmp[x][y];l--)
        cnt++;
    for(r=x+1;r<=N&&tmp[r][y]==tmp[x][y];r++)
        cnt++;
    if(cnt>=3)
        for(int i=l+1;i<r;i++)
            del[++dtp]=(make_pair(i,y));
    cnt=0;
    for(l=y;l>0&&tmp[x][l]==tmp[x][y];l--)
        cnt++;
    for(r=y+1;r<=M&&tmp[x][r]==tmp[x][y];r++)
        cnt++;
    if(cnt>=3)
        for(int i=l+1;i<r;i++)
            del[++dtp]=(make_pair(x,i));
}

void Fall(int tmp[N+3][M+3],int x,int y)
{
    int ground=y-1;
    while(ground>0&&tmp[x][ground]==0)
        ground--;
    int obj=y;
    while(obj<=M&&tmp[x][obj]==0)
        obj++;
    if(ground==obj-1)
        Update(tmp,x,y);
    else
    {
        int i;
        for(i=0;i+obj<=M&&tmp[x][i+obj];i++)
            swap(tmp[x][ground+1+i],tmp[x][i+obj]);

        for(int j=0;j<i;j++)
            Update(tmp,x,ground+1+j);
    }
}

bool Process()
{
    while(qtp[id])
    {
        while(qtp[id])
        {
            int x=Q[id][qtp[id]].first,y=Q[id][qtp[id]].second;
            qtp[id]--;
            Fall(col,x,y);
        }
        while(dtp)
        {
            int i=del[dtp].first,j=del[dtp].second;
            dtp--;
            if(col[i][j])
            {
                col[i][j]=0;
                cnt--;
                Q[id^1][++qtp[id^1]]=make_pair(i,j);
            }
        }
        id^=1;
    }
    return true;
}

void print(int step)
{
    for(int i=1;i<step;i++)
        printf("%d %d %d\n",ans[i][0]-1,ans[i][1]-1,ans[i][2]);
    fclose(stdin);
    fclose(stdout);
    exit(0);
}

void dfs(int step)
{
    if(step>lim)
    {
        if(cnt==0)
            print(step);
        return;
    }
    if(cnt==0)
       return;
    int tmp[N+3][M+3],tcnt=cnt;
    memcpy(tmp,col,sizeof tmp);
    for(int X=1;X<=N;X++)
        for(int Y=1;tmp[X][Y];Y++)
        {
            cnt=tcnt;
            memcpy(col,tmp,sizeof tmp);
            if(X!=N)
            {
                swap(col[X][Y],col[X+1][Y]);
                id=0;
                qtp[0]=qtp[1]=0;
                Q[id][++qtp[id]]=(make_pair(X,Y));
                Q[id][++qtp[id]]=(make_pair(X+1,Y));
                if(Process())
                {
                    ans[step][0]=X;
                    ans[step][1]=Y;
                    ans[step][2]=1;
                    dfs(step+1);
                }
            }
            cnt=tcnt;
            memcpy(col,tmp,sizeof tmp);
            if(X!=1)
            {
                swap(col[X][Y],col[X-1][Y]);
                id=0;
                Q[id][++qtp[id]]=(make_pair(X,Y));
                Q[id][++qtp[id]]=(make_pair(X-1,Y));
                if(Process())
                {
                    ans[step][0]=X;
                    ans[step][1]=Y;
                    ans[step][2]=-1;
                    dfs(step+1);
                }
            }
        }
}

int main()
{
    scanf("%d",&lim);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;;j++)
        {
            scanf("%d",&col[i][j]);
            cnt++;
            if(col[i][j]==0)
                break;
        }
        cnt--;
    }

    dfs(1);
    puts("-1");

    return 0;
}
