#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500005;

int N,M,S,P;
bool ispub[MAXN];
int val[MAXN];
vector<int> adj[MAXN];

int dfn[MAXN],low[MAXN],dfc;
bool anc[MAXN];
int blkid[MAXN],blkc;
int stk[MAXN],tp;

void tarjan(int u)
{
    dfn[u]=++dfc;
    low[u]=dfn[u];
    anc[u]=true;
    stk[++tp]=u;
    for(int i=0;i<(int)adj[u].size();i++)
    {
        int v=adj[u][i];
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(anc[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u])
    {
        blkc++;
        do
        {
            anc[stk[tp]]=false;
            blkid[stk[tp]]=blkc;
            tp--;
        }while(stk[tp+1]!=u);
    }
}

vector<int> adj2[MAXN],radj[MAXN];
long long val2[MAXN],dp[MAXN];
int deg[MAXN];
bool ispub2[MAXN];
queue<int> Q;

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        adj[x].push_back(y);
    }
    for(int i=1;i<=N;i++)
        scanf("%d",&val[i]);
    scanf("%d%d",&S,&P);
    for(int i=1;i<=P;i++)
    {
        int p;
        scanf("%d",&p);
        ispub[p]=true;
    }

    for(int i=1;i<=N;i++)
        if(!dfn[i])
            tarjan(i);
    for(int u=1;u<=N;u++)
    {
        val2[blkid[u]]+=val[u];
        ispub2[blkid[u]]|=ispub[u];
        for(int i=0;i<(int)adj[u].size();i++)
        {
            int v=adj[u][i];
            if(blkid[u]!=blkid[v])
            {
                adj2[blkid[u]].push_back(blkid[v]);
                radj[blkid[v]].push_back(blkid[u]);
                deg[blkid[u]]++;
            }
        }
    }

    for(int i=1;i<=blkc;i++)
        if(deg[i]==0)
            Q.push(i);
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        dp[u]=0;
        for(int i=0;i<(int)adj2[u].size();i++)
        {
            int v=adj2[u][i];
            ispub2[u]|=ispub2[v];
            dp[u]=max(dp[u],dp[v]);
        }
        if(ispub2[u])
            dp[u]+=val2[u];
        else
            dp[u]=0;
        for(int i=0;i<(int)radj[u].size();i++)
        {
            int v=radj[u][i];
            deg[v]--;
            if(deg[v]==0)
                Q.push(v);
        }
    }

    printf("%lld\n",dp[blkid[S]]);
    return 0;
}
