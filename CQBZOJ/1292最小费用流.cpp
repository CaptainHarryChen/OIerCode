#include<cstdio>
#include<cstring>
#include<queue>
#define MAXN 505
using std::queue;
using std::min;
int W[MAXN][MAXN],V[MAXN][MAXN];
int n,m,S,T,ans,flow;
int path[MAXN],dis[MAXN];
bool vis[MAXN];
int SPFA()
{
    memset(vis,0,sizeof vis);
    memset(dis,0x3F,sizeof dis);
    queue<int>Q;
    Q.push(S);
    vis[S]=1;
    dis[S]=0;
    while(!Q.empty())
    {
        int t=Q.front();
        Q.pop();vis[t]=0;
        for(int i=1;i<=n;i++)
            if(W[t][i]>0&&dis[i]>dis[t]+V[t][i])
            {
                dis[i]=dis[t]+V[t][i];
                path[i]=t;
                if(!vis[i])
                {
                    Q.push(i);
                    vis[i]=1;
                }
            }
    }
    if(dis[T]==0x3F3F3F3F)
        return 0;
    int x=T,mn=0x7FFFFFFF;
    while(x!=S)
    {
        mn=min(mn,W[path[x]][x]);
        x=path[x];
    }
    x=T;
    while(x!=S)
    {
        W[path[x]][x]-=mn;
        W[x][path[x]]+=mn;
        x=path[x];
    }
    return mn;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,a,b,w,v;i<=m;i++)
    {
        scanf("%d%d%d%d",&a,&b,&w,&v);
        W[a][b]=w;
        V[a][b]=v;
        V[b][a]=-v;
    }
    S=1;T=n;
    int t;
    while(t=SPFA(),t)
        flow+=t,ans+=dis[T]*t;
    printf("%d\n",ans);
    return 0;
}