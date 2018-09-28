#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=100005;

int N,M,Q;
vector<int> adj[MAXN];
int op[MAXN][3];

int opdep[MAXN],dep[MAXN],col[MAXN];
queue<int> que;

void Mark(int id)
{
    if(opdep[op[id][0]]>=op[id][1])
        return;
    opdep[op[id][0]]=dep[op[id][0]]=op[id][1];
    if(!col[op[id][0]])
        col[op[id][0]]=op[id][2];
    que.push(op[id][0]);
    while(!que.empty())
    {
        int u=que.front();
        que.pop();
        for(int i=0;i<(int)adj[u].size();i++)
        {
            int v=adj[u][i];
            if(opdep[v]>=dep[u]-1)
                continue;
            opdep[v]=dep[u]-1;
            dep[v]=dep[u]-1;
            if(!col[v])
                col[v]=op[id][2];
            que.push(v);
        }
    }
}

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
    scanf("%d",&Q);
    for(int i=1;i<=Q;i++)
        scanf("%d%d%d",&op[i][0],&op[i][1],&op[i][2]);
    memset(opdep,-1,sizeof opdep);
    for(int i=Q;i>=1;i--)
        Mark(i);
    for(int i=1;i<=N;i++)
        printf("%d\n",col[i]);

    return 0;
}
