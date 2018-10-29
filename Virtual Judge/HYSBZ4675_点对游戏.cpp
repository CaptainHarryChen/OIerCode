#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=50005,MAXM=12;

int N,M;
int luck[MAXM];
vector<int> adj[MAXN];

double P[3],ans[3];

int siz[MAXN];
bool vis[MAXN];
int cnt[MAXN],stp[MAXN];

void FindCenter(int u,int tot,pair<int,int> &res,int fa=0)
{
    siz[u]=1;
    int mx=0;
    for(int i=0;i<(int)adj[u].size();i++)
    {
        int v=adj[u][i];
        if(v!=fa&&!vis[v])
        {
            FindCenter(v,tot,res,u);
            siz[u]+=siz[v];
            mx=max(mx,siz[v]);
        }
    }
    mx=max(mx,tot-siz[u]);
    res=min(res,make_pair(mx,u));
}
void CalcAns(int u,int fa,int d,int tm)
{
    for(int i=1;i<=M;i++)
        if(luck[i]-d>=0)
        {
            if(stp[luck[i]-d]!=tm)
            {
                stp[luck[i]-d]=tm;
                cnt[luck[i]-d]=0;
            }
            for(int k=0;k<3;k++)
                ans[k]+=P[k]*cnt[luck[i]-d];
        }
    for(int i=0;i<(int)adj[u].size();i++)
    {
        int v=adj[u][i];
        if(!vis[v]&&v!=fa)
            CalcAns(v,u,d+1,tm);
    }
}
void Update(int u,int fa,int d,int tm)
{
    if(stp[d]!=tm)
    {
        stp[d]=tm;
        cnt[d]=0;
    }
    cnt[d]++;
    for(int i=0;i<(int)adj[u].size();i++)
    {
        int v=adj[u][i];
        if(!vis[v]&&v!=fa)
            Update(v,u,d+1,tm);
    }
}
void TreeDecomposition(int u)
{
    pair<int,int> tmp=make_pair(siz[u],u);
    FindCenter(u,siz[u],tmp);
    u=tmp.second;
    vis[u]=true;

    stp[0]=u;cnt[0]=1;
    for(int i=0;i<(int)adj[u].size();i++)
    {
        int v=adj[u][i];
        if(!vis[v])
        {
            CalcAns(v,u,1,u);
            Update(v,u,1,u);
        }
    }
    for(int i=0;i<(int)adj[u].size();i++)
    {
        int v=adj[u][i];
        if(!vis[v])
            TreeDecomposition(v);
    }
}

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;i++)
        scanf("%d",&luck[i]);
    for(int i=1;i<N;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i=0;i<3;i++)
    {
        int k=(N-i-1)/3+1;
        P[i]=1.0*k*(k-1)/N/(N-1);
    }

    siz[1]=N;
    TreeDecomposition(1);

    for(int i=0;i<3;i++)
        printf("%.2f\n",ans[i]);

    return 0;
}
