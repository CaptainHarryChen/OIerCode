#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=5005,MAXM=10005;

struct Edge
{
	int v;
	Edge *nxt;
}E[MAXM*2],*adj[MAXN],*ecnt=E;
void add_edge(int u,int v)
{
	ecnt->v=v;
	ecnt->nxt=adj[u];
	adj[u]=ecnt++;
	ecnt->v=u;
	ecnt->nxt=adj[v];
	adj[v]=ecnt++;
}

int dfn[MAXN],dfc,low[MAXN];
int cp,ce;
void tarjan(int u,int fa)
{
	dfn[u]=++dfc;
	low[u]=dfn[u];
	int cnt=0;
	bool cutp=false;
	for(Edge *p=adj[u];p;p=p->nxt)
	{
		int v=p->v;
		if(!dfn[v])
		{
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(fa==0)
				cnt++;
			else if(low[v]>=dfn[u])
				cutp=true;
			if(low[v]>dfn[u])
				ce++;
		}
		else if(v!=fa)
			low[u]=min(low[u],dfn[v]);
	}
	if(fa==0&&cnt>1)
		cutp=true;
	cp+=cutp;
}

int cnt[MAXN];
int ans[MAXN];
int main()
{
	freopen("tarjan-undirected_data.in","r",stdin);
	int N,M,a,b;
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d",&a,&b);
		add_edge(a,b);
	}
	tarjan(1,0);
	printf("%d\n%d\n",cp,ce);
	return 0;
}
