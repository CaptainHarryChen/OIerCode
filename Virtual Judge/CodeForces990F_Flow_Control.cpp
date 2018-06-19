#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=200005;

struct Edge
{
	int v,id,dir;
	Edge(int a,int b,int c){v=a;id=b;dir=c;}
};

int n;
int f[MAXN];
vector<Edge> ed[MAXN];
int ans[MAXN];
bool vis[MAXN];

void dfs(int u,int edid=0,int dr=0)
{
	vis[u]=true;
	int sum=0;
	for(int i=0;i<(int)ed[u].size();i++)
	{
		int v=ed[u][i].v;
		if(vis[v])continue;
		dfs(v,ed[u][i].id,ed[u][i].dir);
		sum+=(-ed[u][i].dir)*ans[ed[u][i].id];
	}
	ans[edid]=-dr*(sum-f[u]);
}

int main()
{
	int n,m;
	scanf("%d",&n);
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&f[i]);
		sum+=f[i];
	}
	if(sum!=0)
	{
		puts("Impossible");
		return 0;
	}
	scanf("%d",&m);
	for(int i=1,x,y;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		ed[x].push_back(Edge(y,i,1));
		ed[y].push_back(Edge(x,i,-1));
	}
	
	dfs(1);
	puts("Possible");
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	
	return 0;
}
