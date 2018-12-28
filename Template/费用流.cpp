#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=0x3F3F3F3F;

namespace CostFlow
{
    const int MAX_NODE=505,MAX_EDGE=250005;
    struct Edge
    {
        int v,cap,val;
        Edge *nxt,*bck;
        Edge(){}
        Edge(int _v,int _c,int _val,Edge *n,Edge *b)
        {v=_v;cap=_c;val=_val;nxt=n;bck=b;}
    }edges[MAX_EDGE*2],*adj[MAX_NODE],*adj2[MAX_NODE],*ed_it=edges;

    void AddEdge(int u,int v,int c,int val)
    {
        *ed_it=Edge(v,c,val,adj[u],ed_it+1);
        adj[u]=ed_it;
        ed_it++;
        *ed_it=Edge(u,0,-val,adj[v],ed_it-1);
        adj[v]=ed_it;
        ed_it++;
    }

    deque<int> Q;
    int dis[MAX_NODE];
    bool inq[MAX_NODE],vis[MAX_NODE];
    int value;

    int aug(int u,int T,int augco=0x3F3F3F3F)
    {
        if(u==T)
            return augco;
        int augc=augco;
        vis[u]=true;
        for(Edge *&e=adj2[u];e;e=e->nxt)
            if(e->cap>0&&!vis[e->v]&&dis[e->v]==dis[u]-e->val)
            {
                int delta=min(e->cap,augc);
                delta=aug(e->v,T,delta);
                e->cap-=delta;
                e->bck->cap+=delta;
                augc-=delta;
                value+=delta*e->val;
                if(augc==0)
                    break;
            }
		vis[u]=false;
        return augco-augc;
    }
    bool relable(int S,int T)
    {
        memset(dis,0x3F,sizeof dis);
        dis[T]=0;
        Q.push_front(T);inq[T]=true;
        while(!Q.empty())
        {
            int u=Q.front();
            Q.pop_front();inq[u]=false;
            for(Edge *e=adj[u];e;e=e->nxt)
                if(e->bck->cap)
                {
                    int v=e->v;
                    if(dis[v]>dis[u]-e->val)
                    {
                        dis[v]=dis[u]-e->val;
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
        return dis[S]<INF;
    }

    void Solve(int S,int T,int &ans_flow,int &ans_val)
    {
        ans_flow=ans_val=0;
        while(relable(S,T))
        {
            memset(vis,0,sizeof vis);
            memcpy(adj2,adj,sizeof adj);
            ans_flow+=aug(S,T);
        }
        ans_val=value;
    }
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v,c,w;
		scanf("%d%d%d%d",&u,&v,&c,&w);
		CostFlow::AddEdge(u,v,c,w);
	}
	int flow,val;
	CostFlow::Solve(1,n,flow,val);
	printf("%d\n",val);
	return 0;
}
