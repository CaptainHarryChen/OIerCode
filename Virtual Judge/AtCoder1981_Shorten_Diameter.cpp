#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=2005;

int N,K;
vector<int> adj[MAXN];
int dep[MAXN],fa[MAXN],cnt;

void dfs(int u,int f,int lim)
{
    for(int i=0;i<(int)adj[u].size();i++)
    {
        int v=adj[u][i];
        if(v!=f)
        {
            dep[v]=dep[u]+1;
            if(dep[v]>lim)
                cnt++;
            dfs(v,u,lim);
        }
    }
}

int main()
{
    scanf("%d%d",&N,&K);
    for(int i=1;i<N;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int ans=0x3F3F3F3F;
    if(K%2==0)
    {
        for(int i=1;i<=N;i++)
        {
            cnt=0;
            dep[i]=0;dfs(i,0,K/2);
            ans=min(ans,cnt);
        }
    }
    else
    {
        for(int i=1;i<=N;i++)
            for(int j=0;j<(int)adj[i].size();j++)
            {
                cnt=0;
                dep[i]=0;dfs(i,adj[i][j],K/2);
                dep[adj[i][j]]=0;dfs(adj[i][j],i,K/2);
                ans=min(ans,cnt);
            }
    }

    printf("%d\n",ans);

    return 0;
}