#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1005,MAXM=1000005;

struct Graph
{
    struct AdjEdge
    {
        int v;
        AdjEdge *nxt;
    }edges[MAXM*2],*adj[MAXN],*edges_it;

    void Clear()
    {
        memset(adj,0,sizeof adj);
        edges_it=edges;
    }
    void AddEdge(int u,int v)
    {
		//printf("%d->%d\n",u,v);
        edges_it->v=v;
        edges_it->nxt=adj[u];
        adj[u]=edges_it++;
    }
};

int n,m;
Graph G;
bool use[MAXN];
int col[MAXN];

int dfn[MAXN],low[MAXN],dfc;
int stk[MAXN],tp;
int blkid[MAXN],blkc;

bool Check(int u,int c=1)
{
	if(col[u]!=0)
	{
		if(col[u]==c)
			return true;
		return false;
	}
	col[u]=c;
	for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
	{
		int v=e->v;
		if(blkid[v]!=blkc)
			continue;
		if(!Check(v,c==1?2:1))
			return false;
	}
	return true;
}

void tarjan(int u,int fa=0)
{
	low[u]=dfn[u]=++dfc;
	stk[++tp]=u;
	for(Graph::AdjEdge *e=G.adj[u];e;e=e->nxt)
	{
		int v=e->v;
		if(v==fa)
			continue;
		if(!dfn[v])
		{
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u])
			{
				blkc++;
				int cnt=0,tmp=tp;
				do
				{
					blkid[stk[tp]]=blkc;
					tp--;
					cnt++;
				}while(stk[tp+1]!=v);
				blkid[u]=blkc;
				if(cnt>1&&Check(u)==false)
				{
					for(int i=tp+1;i<=tmp;i++)
						use[stk[i]]=true;
					use[u]=true;
				}
				for(int i=tp+1;i<=tmp;i++)
					col[stk[i]]=0;
				col[u]=0;
			}
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
	
}

bool argu[MAXN][MAXN];

void Init()
{
	G.Clear();
	memset(argu,0,sizeof argu);
	dfc=0;blkc=0;tp=0;
	memset(col,0,sizeof col);
	memset(use,0,sizeof use);
	memset(dfn,0,sizeof dfn);
	memset(blkid,0,sizeof blkid);
}

int main()
{
	for(;;)
	{
		scanf("%d%d",&n,&m);
		if(n==0&&m==0)
			break;
		
		Init();
		
		for(int i=1;i<=m;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			argu[u][v]=argu[v][u]=true;
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(i!=j&&!argu[i][j])
					G.AddEdge(i,j);
		
		for(int i=1;i<=n;i++)
			if(!dfn[i])
				tarjan(i);
		
		int ans=0;
		for(int i=1;i<=n;i++)
			ans+=(use[i]==false);
		printf("%d\n",ans);
	}
	

    return 0;
}
