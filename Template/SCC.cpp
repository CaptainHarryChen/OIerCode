#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=500005;

int N,M;
vector<int> adj[MAXN],adj2[MAXN];

int dfn[MAXN],low[MAXN],dfc;
int stk[MAXN],tp;
bool anc[MAXN];
int blkid[MAXN],blkc;

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
			blkid[stk[tp]]=blkc;
			anc[stk[tp]]=false;
			tp--;
		}while(stk[tp+1]!=u);
	}
}
void BuildGraph()
{
	for(int u=1;u<=N;u++)
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i];
			if(blkid[u]==blkid[v])
				continue;
			adj2[blkid[u]].push_back(blkid[v]);
		}
}

int main()
{
	freopen("SCC_data.in","r",stdin);
	
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		adj[x].push_back(y);
	}
	
	for(int i=1;i<=N;i++)
		if(dfn[i]==0)
			tarjan(i);
	BuildGraph();
	
	printf("Block id:");
	for(int i=1;i<=N;i++)
		printf("%d ",blkid[i]);
	puts("");
	puts("Edge:");
	for(int i=1;i<=N;i++)
		for(int j=0;j<(int)adj2[i].size();j++)
			printf("%d->%d\n",i,adj2[i][j]);
	
	return 0;
}
