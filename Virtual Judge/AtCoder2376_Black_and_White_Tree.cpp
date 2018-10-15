#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005;
 
int N;
vector<int> adj[MAXN];
int col[MAXN];
 
bool dfs(int u,int f)
{
    if(adj[u].size()==1U)
    {
        col[u]=0;
        return false;
    }
    int cnt[2]={0};
    for(int i=0;i<(int)adj[u].size();i++)
    {
        int v=adj[u][i];
        if(v==f)
            continue;
        if(dfs(v,u))
            return true;
        cnt[col[v]]++;
    }
    if(cnt[0]>=2)
        return true;
	if(f==0&&(int)adj[u].size()==cnt[1])
		return true;
    if(cnt[0])
        col[u]=1;
    else
        col[u]=0;
    return false;
}
 
int main()
{
    scanf("%d",&N);
    for(int i=1;i<N;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if(N==2)
        puts("Second");
    else
    {
        bool ans;
        for(int i=1;i<=N;i++)
            if(adj[i].size()>1U)
            {
                ans=dfs(i,0);
                break;
            }
        puts(ans?"First":"Second");
    }
 
    return 0;
}
