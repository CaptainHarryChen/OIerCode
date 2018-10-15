#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXNODE=5005,MAXEDGE=10005,MAXN=53;

struct Graph
{
    struct AdjEdge
    {
        int v;
        AdjEdge *nxt;
    }edges[MAXEDGE],*adj[MAXNODE],*edges_it;

    void Clear()
    {
        memset(adj,0,sizeof adj);
        edges_it=edges;
    }
    void AddEdge(int u,int v)
    {
        //printf("%d %d\n",u,v);
        edges_it->v=v;
        edges_it->nxt=adj[u];
        adj[u]=edges_it++;
    }
};

int N,M,R,C;
char mp[MAXN][MAXN];

int ID(int x,int y,int d)
{return ((x-1)*M+y)*2-1+d;}
bool check(int x,int y)
{return x>0&&y>0&&x<=N&&y<=M&&mp[x][y]=='.';}

Graph G;
int vis[MAXNODE],nxt[MAXNODE];

bool aug(int s,int u)
{
    for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
    {
        int v=e->v;
        if(vis[v]==s)
            continue;
        vis[v]=s;
        if(!nxt[v]||aug(s,nxt[v]))
        {
            nxt[v]=u;
            return true;
        }
    }
    return false;
}

int Hungary()
{
    int res=0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            if(check(i,j))
                res+=aug(ID(i,j,1),ID(i,j,1));
    return res;
}

int main()
{
    scanf("%d%d%d%d",&N,&M,&R,&C);

    int cnt=0;
    for(int i=1;i<=N;i++)
    {
        scanf("%s",mp[i]+1);
        for(int j=1;j<=M;j++)
            cnt+=mp[i][j]=='.';
    }

    G.Clear();
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            if(mp[i][j]=='.')
            {
                int u=ID(i,j,1);
                if(check(i+R,j+C))
                    G.AddEdge(u,ID(i+R,j+C,0));
                if(check(i+R,j-C))
                    G.AddEdge(u,ID(i+R,j-C,0));
                if(check(i+C,j+R))
                    G.AddEdge(u,ID(i+C,j+R,0));
                if(check(i+C,j-R))
                    G.AddEdge(u,ID(i+C,j-R,0));
            }

    int ans=Hungary();
    ans=cnt-ans;
    printf("%d\n",ans);

    return 0;
}
