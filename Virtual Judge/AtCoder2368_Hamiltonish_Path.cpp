#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int N,M;
vector<int> adj[MAXN];
vector<int> ans;
bool vis[MAXN];

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool flag=false;
    ans.push_back(1);
    vis[1]=true;
    for(int i=0;i<(int)adj[1].size();i++)
    {
        int u=adj[1][i];
        if(vis[u])
            continue;
        vis[u]=true;
        bool go=true;
        while(go)
        {
            go=false;
            ans.push_back(u);
            for(int j=0;j<(int)adj[u].size();j++)
            {
                int v=adj[u][j];
                if(vis[v])
                    continue;
                vis[v]=true;
                go=true;
                u=v;
                break;
            }
        }
        if(!flag)
        {
            reverse(ans.begin(),ans.end());
            flag=true;
        }
        else
            break;
    }
    printf("%u\n",ans.size());
    for(int i=0;i<(int)ans.size();i++)
        printf("%d%c",ans[i]," \n"[i==(int)ans.size()-1]);

    return 0;
}
