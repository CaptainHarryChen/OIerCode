#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=805;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

int H,W,K;
char maze[MAXN][MAXN];

int step[MAXN][MAXN];
pair<int,int> st;
queue<pair<int,int> > Q;

int main()
{
    scanf("%d%d%d",&H,&W,&K);
    for(int i=1;i<=H;i++)
    {
        scanf("%s",maze[i]+1);
        for(int j=1;j<=W;j++)
            if(maze[i][j]=='S')
                st.first=i,st.second=j;
    }

    memset(step,-1,sizeof step);
    step[st.first][st.second]=0;
    Q.push(st);
    int ans=0x3F3F3F3F;
    while(!Q.empty())
    {
        pair<int,int> u=Q.front();
        Q.pop();

        ans=min(ans,(u.first-1+K-1)/K+1);
        ans=min(ans,(u.second-1+K-1)/K+1);
        ans=min(ans,(H-u.first+K-1)/K+1);
        ans=min(ans,(W-u.second+K-1)/K+1);

        if(step[u.first][u.second]>=K)
            continue;

        for(int d=0;d<4;d++)
        {
            pair<int,int> v=u;
            v.first+=dir[d][0],v.second+=dir[d][1];
            if(step[v.first][v.second]==-1&&maze[v.first][v.second]!='#')
            {
                step[v.first][v.second]=step[u.first][u.second]+1;
                Q.push(v);
            }
        }
    }

    printf("%d\n",ans);

    return 0;
}
