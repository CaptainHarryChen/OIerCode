#include<cstdio>
#include<cstring>
#include<deque>
#include<algorithm>
using namespace std;
const int MAXN=25005,MAXM=100005;

struct Graph
{
    struct AdjEdge
    {
        int v,d;
        AdjEdge *nxt;
    }edges[MAXM*2],*adj[MAXN],*edges_it;

    void Clear()
    {
        memset(adj,0,sizeof adj);
        edges_it=edges;
    }
    void AddEdge(int u,int v,int d)
    {
        edges_it->v=v;
        edges_it->d=d;
        edges_it->nxt=adj[u];
        adj[u]=edges_it++;
    }
};

int T,R,P,S;
Graph G;

int dis[MAXN];
bool inq[MAXN];
deque<int> Q;

void SPFA_SLF(int S)
{
    memset(dis,0x3F,sizeof dis);
    memset(inq,0,sizeof inq);
    Q.push_front(S);
    dis[S]=0;
    inq[S]=true;
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop_front();
        inq[u]=false;
        for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
        {
            int v=e->v;
            if(dis[v]>dis[u]+e->d)
            {
                dis[v]=dis[u]+e->d;
                if(!inq[v])
                {
                    if(Q.empty()||dis[v]<dis[Q.front()])
                        Q.push_front(v);
                    else
                        Q.push_back(v);
                    inq[v]=true;
                }
            }
        }
    }
}

int main()
{
    scanf("%d%d%d%d",&T,&R,&P,&S);
    G.Clear();
    for(int i=1;i<=R;i++)
    {
        int u,v,d;
        scanf("%d%d%d",&u,&v,&d);
        G.AddEdge(u,v,d);
        G.AddEdge(v,u,d);
    }
    for(int i=1;i<=P;i++)
    {
        int u,v,d;
        scanf("%d%d%d",&u,&v,&d);
        G.AddEdge(u,v,d);
    }

    SPFA_SLF(S);
    for(int i=1;i<=T;i++)
        if(dis[i]==0x3F3F3F3F)
            puts("NO PATH");
        else
            printf("%d\n",dis[i]);

    return 0;
}
