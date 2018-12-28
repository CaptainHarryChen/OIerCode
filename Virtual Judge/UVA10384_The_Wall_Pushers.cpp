#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
const char id[5]="WNES";

char ans[1000];
int wall[4][6];
int x,y,lastx,lasty;

int h()
{
    int ret=0x3F3F3F3F;
    for(int j=0;j<6;j++)
        if((wall[0][j]&2)==0)
            ret=min(ret,abs(x-0)+abs(y-j)+1);
    for(int j=0;j<6;j++)
        if((wall[3][j]&8)==0)
            ret=min(ret,abs(x-3)+abs(y-j)+1);
    for(int i=0;i<4;i++)
        if((wall[i][0]&1)==0)
            ret=min(ret,abs(x-i)+abs(y-0)+1);
    for(int i=0;i<4;i++)
        if((wall[i][5]&4)==0)
            ret=min(ret,abs(x-i)+abs(y-5)+1);
    return ret;
}

bool dfs(int rest)
{
    if(x<0||y<0||x>=4||y>=6)
        return true;
    if(h()>rest)
        return false;
    //printf("go to (%d,%d)\n",x,y);
    int tlx=lastx,tly=lasty;
    for(int d=0;d<4;d++)
    {
        if((wall[x][y]&(1<<d))==0&&(x+dir[d][0]!=lastx||y+dir[d][1]!=lasty))
        {
            lastx=x;lasty=y;
            x+=dir[d][0];y+=dir[d][1];
            ans[rest]=id[d];
            if(dfs(rest-1))
                return true;
            x-=dir[d][0];y-=dir[d][1];
            lastx=tlx;lasty=tly;
        }
        else if(x+dir[d][0]>=0&&x+dir[d][0]<4&&y+dir[d][1]>=0&&y+dir[d][1]<6&&(wall[x+dir[d][0]][y+dir[d][1]]&(1<<d))==0)
        {
            wall[x][y]^=(1<<d);
            lastx=x;lasty=y;
            x+=dir[d][0];y+=dir[d][1];
            wall[x][y]^=(1<<d);
            wall[x][y]^=(1<<((d+2)%4));
            if(x+dir[d][0]>=0&&x+dir[d][0]<4&&y+dir[d][1]>=0&&y+dir[d][1]<6)
                wall[x+dir[d][0]][y+dir[d][1]]^=(1<<((d+2)%4));
            ans[rest]=id[d];
            if(dfs(rest-1))
                return true;
            wall[x][y]^=(1<<d);
            wall[x][y]^=(1<<((d+2)%4));
            if(x+dir[d][0]>=0&&x+dir[d][0]<4&&y+dir[d][1]>=0&&y+dir[d][1]<6)
                wall[x+dir[d][0]][y+dir[d][1]]^=(1<<((d+2)%4));
            x-=dir[d][0];y-=dir[d][1];
            wall[x][y]^=(1<<d);
            lastx=tlx;lasty=tly;
        }
    }
    //printf("back from (%d,%d)\n",x,y);
    return false;
}

int main()
{
    int stx,sty;
    for(;;)
    {
        scanf("%d%d",&sty,&stx);
        if(stx==0&&sty==0)
            break;
        stx--;sty--;
        for(int i=0;i<4;i++)
            for(int j=0;j<6;j++)
                scanf("%d",&wall[i][j]);

        for(int lim=1;;lim++)
        {
            x=stx;y=sty;
            lastx=lasty=-1;
            //printf("deep limit %d \nbegin dfs\n",lim);
            if(dfs(lim))
            {
                reverse(ans+1,ans+lim+1);
                ans[lim+1]=0;
                puts(ans+1);
                break;
            }
        }
    }

    return 0;
}
