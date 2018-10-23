#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=55;

class DeerInZooDivOne
{
    struct Graph
    {
        struct Edge
        {
            int v,w,cap;
            Edge *nxt,*bck;
        }edges[MAXN*MAXN*4],*adj[MAXN],*edges_it;
        void Clear()
        {
            memset(adj,0,sizeof adj);
            edges_it=edges;
        }
        void AddEdge(int u,int v)
        {
            edges_it->v=v;
            edges_it->nxt=adj[u];
            adj[u]=edges_it++;
        }
        void AddNetEdge(int u,int v,int w,int c)
        {
            edges_it->v=v;edges_it->w=w;edges_it->cap=c;
            edges_it->nxt=adj[u];edges_it->bck=edges_it+1;
            adj[u]=edges_it++;
            edges_it->v=u;edges_it->w=0;edges_it->cap=-c;
            edges_it->nxt=adj[v];edges_it->bck=edges_it-1;
            adj[v]=edges_it++;
        }
    };

    int n;
    Graph Tree,net;
    int dp[MAXN][MAXN][MAXN][MAXN];
    vector<int> A,B;

    pair<int,int> SPFA(int S,int T)
    {
        static int dis[MAXN];
        static Graph::Edge *path[MAXN];
        static bool inq[MAXN];
        static queue<int> Q;
        memset(dis,-1,sizeof dis);
        memset(inq,0,sizeof inq);
        dis[S]=0;
        inq[S]=true;
        Q.push(S);
        while(!Q.empty())
        {
            int u=Q.front();
            inq[u]=false;
            Q.pop();
            for(Graph::Edge *e=net.adj[u];e;e=e->nxt)
                if(e->cap>0)
                {
                    int v=e->v;
                    if(dis[v]<dis[u]+e->w)
                    {
                        dis[v]=dis[u]+e->w;
                        path[v]=e;
                        if(!inq[v])
                        {
                            inq[v]=true;
                            Q.push(v);
                        }
                    }
                }
        }
        if(dis[T]==-1)
            return make_pair(0,0);
        int x=T,flow=0x3F3F3F3F;
        while(x!=S)
        {
            flow=min(flow,path[x]->cap);
            x=path[x]->bck->v;
        }
        x=T;
        while(x!=S)
        {
            path[x]->cap-=flow;
            path[x]->bck->cap+=flow;
            x=path[x]->bck->v;
        }
        return make_pair(flow,dis[T]);
    }
    int ValueNetFlow(int S,int T)
    {
        int res=0;
        pair<int,int> t;
        while(t=SPFA(S,T),t.first!=0)
            res+=t.first*t.second;
        return res;
    }

    void Mark(int u,int fa,vector<int> &s)
    {
        s.push_back(u);
        for(Graph::Edge *e=Tree.adj[u];e;e=e->nxt)
        {
            int v=e->v;
            if(v==fa)
                continue;
            Mark(v,u,s);
        }
    }
    int DP(int ti,int a,int faa,int b,int fab)
    {
        if(dp[a][faa][b][fab]!=-1)
            return dp[a][faa][b][fab];
        dp[a][faa][b][fab]=0;
        int cnt1=0,cnt2=0;
        for(Graph::Edge *e1=Tree.adj[a];e1;e1=e1->nxt)
            cnt1+=(e1->v!=faa);
        for(Graph::Edge *e2=Tree.adj[b];e2;e2=e2->nxt)
            cnt2+=(e2->v!=fab);
        if(cnt1==0||cnt2==0)
            return dp[a][faa][b][fab]=1;

        for(Graph::Edge *e1=Tree.adj[a];e1;e1=e1->nxt)
            if(e1->v!=faa)
                for(Graph::Edge *e2=Tree.adj[b];e2;e2=e2->nxt)
                    if(e2->v!=fab)
                        DP(ti,e1->v,a,e2->v,b);

        net.Clear();
        int S=n,T=n+1;
        for(Graph::Edge *e2=Tree.adj[b];e2;e2=e2->nxt)
        {
            int v=e2->v;
            if(v==fab)
                continue;
            net.AddNetEdge(v,T,0,1);
        }
        for(Graph::Edge *e1=Tree.adj[a];e1;e1=e1->nxt)
        {
            int u=e1->v;
            if(u==faa)
                continue;
            net.AddNetEdge(S,u,0,1);
            for(Graph::Edge *e2=Tree.adj[b];e2;e2=e2->nxt)
            {
                int v=e2->v;
                if(v==fab)
                    continue;
                net.AddNetEdge(u,v,dp[u][a][v][b],1);
            }
        }
        return dp[a][faa][b][fab]=ValueNetFlow(S,T)+1;
    }

public:
    int getmax(const vector<int> &a,const vector<int> &b)
    {
        n=a.size()+1;

        int ans=0;
        for(int i=0;i<n-1;i++)
        {
            A.clear();
            B.clear();
            Tree.Clear();
            for(int j=0;j<n-1;j++)
                if(j!=i)
                {
                    Tree.AddEdge(a[j],b[j]);
                    Tree.AddEdge(b[j],a[j]);
                }
            Mark(a[i],b[i],A);
            Mark(b[i],a[i],B);
			memset(dp,-1,sizeof dp);
            for(int j=0;j<(int)A.size();j++)
                for(int k=0;k<(int)B.size();k++)
                    ans=max(ans,DP(i,A[j],n,B[k],n));
        }
        return ans;
    }
};