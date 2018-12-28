#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=16;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

struct Node
{
    int pos[3];
    bool rev;
};

int h,w,n;
char grid[MAXN+5][MAXN+5];

int adj[MAXN*MAXN+10][6];

Node start,goal;
queue<Node> Q;
short step[2][MAXN*MAXN+1][MAXN*MAXN+1][MAXN*MAXN+1];

void GetStartGoal()
{
    start.pos[0]=start.pos[1]=start.pos[2]=0;
    goal.pos[0]=goal.pos[1]=goal.pos[2]=0;
    start.rev=false;
    goal.rev=true;
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++)
        {
            if(grid[i][j]>='a'&&grid[i][j]<='c')
                start.pos[grid[i][j]-'a']=(i-1)*w+j;
            if(grid[i][j]>='A'&&grid[i][j]<='C')
                goal.pos[grid[i][j]-'A']=(i-1)*w+j;
        }
}

void PreProcess()
{
    adj[0][0]=1;
    adj[0][1]=0;
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++)
            if(grid[i][j]!='#')
            {
                int u=(i-1)*w+j;
                int &tp=adj[u][0];
                tp=0;
                for(int d=0;d<4;d++)
                {
                    int x=i+dir[d][0],y=j+dir[d][1];
                    if(x>0&&y>0&&x<=h&&y<=w&&grid[x][y]!='#')
                        adj[u][++tp]=(x-1)*w+y;
                }
                adj[u][++tp]=u;
            }
}

int BFS()
{
    memset(step,-1,sizeof step);
    while(!Q.empty())
        Q.pop();
    step[0][start.pos[0]][start.pos[1]][start.pos[2]]=0;
    step[1][goal.pos[0]][goal.pos[1]][goal.pos[2]]=0;
    Q.push(start);
    Q.push(goal);
    while(!Q.empty())
    {
        Node u=Q.front(),v;
        Q.pop();
        int ty=u.rev,p1=u.pos[0],p2=u.pos[1],p3=u.pos[2];
        v.rev=ty;
        int np1,np2,np3;
        for(int i=1;i<=adj[p1][0];i++)
        {
            np1=adj[p1][i];
            for(int j=1;j<=adj[p2][0];j++)
            {
                np2=adj[p2][j];
                if(np2!=0&&(np2==np1||(np2==p1&&np1==p2)))
                    continue;
                for(int k=1;k<=adj[p3][0];k++)
                {
                    np3=adj[p3][k];
                    if(np3!=0&&(np3==np1||np3==np2||(np3==p1&&np1==p3)||(np3==p2&&np2==p3)))
                        continue;
                    if(step[ty][np1][np2][np3]!=-1)
                        continue;
                    step[ty][np1][np2][np3]=step[ty][p1][p2][p3]+1;
                    if(step[ty^1][np1][np2][np3]!=-1)
                        return step[ty^1][np1][np2][np3]+step[ty][np1][np2][np3];
                    v.pos[0]=np1,v.pos[1]=np2,v.pos[2]=np3;
                    Q.push(v);
                }
            }
        }
    }
    return -1;
}

int main()
{
    for(;;)
    {
        scanf("%d%d%d",&w,&h,&n);
        if(h==0&&w==0&&n==0)
            break;
        gets(grid[0]);
        for(int i=1;i<=h;i++)
            gets(grid[i]+1);

        GetStartGoal();
        PreProcess();
        printf("%d\n",BFS());
    }

    return 0;
}
