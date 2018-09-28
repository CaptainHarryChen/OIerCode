#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=1005;

struct Point
{
    int x,y,z;
};

bool G[MAXN][MAXN];
bool reach[MAXN];
Point hole[MAXN];

long long dist(const Point &a,const Point &b)
{
    return 1LL*(a.x-b.x)*(a.x-b.x)+1LL*(a.y-b.y)*(a.y-b.y)+1LL*(a.z-b.z)*(a.z-b.z);
}

queue<int> Q;

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        memset(G,0,sizeof G);
        int n,h,r;
        scanf("%d%d%d",&n,&h,&r);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&hole[i].x,&hole[i].y,&hole[i].z);
        for(int i=1;i<=n;i++)
        {
            if(hole[i].z-r<=0)
                G[0][i]=G[i][0]=true;
            for(int j=i+1;j<=n;j++)
            {
				Point a=hole[i];
				Point b=hole[j];
                if(1LL*(a.x-b.x)*(a.x-b.x)+1LL*(a.y-b.y)*(a.y-b.y)<=4LL*r*r-1LL*(a.z-b.z)*(a.z-b.z))
                    G[i][j]=G[j][i]=true;
            }
            if(hole[i].z+r>=h)
                G[i][n+1]=G[n+1][i]=true;
        }

        memset(reach,0,sizeof reach);
        reach[0]=true;
        Q.push(0);
        while(!Q.empty())
        {
            int u=Q.front();
            Q.pop();
            for(int i=1;i<=n+1;i++)
                if(!reach[i]&&G[u][i])
                {
                    reach[i]=true;
                    Q.push(i);
                }
        }
        if(reach[n+1])
            puts("Yes");
        else
            puts("No");
    }

    return 0;
}
