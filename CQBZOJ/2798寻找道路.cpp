#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=10005;

int n,m,s,t;
vector<int> adj[MAXN],radj[MAXN];
int dis[MAXN];
bool mk[MAXN],chk[MAXN],vis[MAXN];
queue<int> Q;

void Mark(int u)
{
    mk[u]=true;
    for(int i=0;i<(int)radj[u].size();i++)
    {
        int v=radj[u][i];
        if(!mk[v])
            Mark(v);
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        adj[u].push_back(v);
        radj[v].push_back(u);
    }
    scanf("%d%d",&s,&t);
    Mark(t);
    if(!mk[s])
        puts("-1");
    else
    {
        for(int u=1;u<=n;u++)
        {
            chk[u]=true;
            for(int i=0;i<(int)adj[u].size();i++)
            {
                int v=adj[u][i];
                if(!mk[v])
                {
                    chk[u]=false;
                    break;
                }
            }
        }
        vis[s]=true;
        dis[s]=0;
        Q.push(s);
        while(!Q.empty())
        {
            int u=Q.front();
            Q.pop();
            for(int i=0;i<(int)adj[u].size();i++)
            {
                int v=adj[u][i];
                if(!vis[v]&&chk[v])
                {
                    dis[v]=dis[u]+1;
                    vis[v]=true;
                    Q.push(v);
                }
            }
        }
        if(!vis[t])
            puts("-1");
        else
            printf("%d\n",dis[t]);
    }
    return 0;
}
