#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=500005;

struct Edge
{int v,id,type;};

int n,m;
int E[MAXN][2];
int deg[MAXN];
vector<Edge> adj[MAXN];

void AddEdge(int u,int v,int t,int i)
{
	static Edge e;
	e.v=v,e.id=i,e.type=t;
	adj[u].push_back(e);
	e.v=u,e.type=-t;
	adj[v].push_back(e);
}

bool visE[MAXN*2],vis[MAXN];
int ans;
vector<int> ansE[MAXN];
void eular(int u)
{
	vis[u]=true;
	for(int i=0;i<(int)adj[u].size();i++)
		if(!visE[adj[u][i].id])
		{
			visE[adj[u][i].id]=true;
			eular(adj[u][i].v);
			if(adj[u][i].type!=0)
				ansE[ans].push_back(-adj[u][i].id*adj[u][i].type);
			else if(ansE[ans].size())
				ansE[++ans].clear();
		}
}

int main()
{
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(int i=1;i<=n;i++)
			adj[i].clear();
		memset(deg,0,sizeof deg);
		memset(visE,0,sizeof visE);
		memset(vis,0,sizeof vis);
		ans=0;
		for(int i=1;i<=m;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			//AddEdge(u,v,1,i);
			E[i][0]=u;E[i][1]=v;
			deg[u]++;deg[v]++;
		}
		int odd=-1,cntE=m;
		for(int i=1;i<=n;i++)
			if(deg[i]%2)
			{
				if(odd!=-1)
					AddEdge(odd,i,0,++cntE),odd=-1;
				else
					odd=i;
			}
		for(int i=1;i<=m;i++)
			AddEdge(E[i][0],E[i][1],1,i);
		for(int i=1;i<=n;i++)
			if(!vis[i]&&(deg[i]%2))
			{
				ansE[++ans].clear();
				eular(i);
				while(!ansE[ans].size()&&ans)
					ans--;
			}
		for(int i=1;i<=n;i++)
			if(!vis[i]&&deg[i])
			{
				ansE[++ans].clear();
				eular(i);
				while(!ansE[ans].size()&&ans)
					ans--;
			}
		printf("%d\n",ans);
		for(int i=1;i<=ans;i++)
		{
			int k=(int)ansE[i].size();
			printf("%d ",k);
			for(int j=0;j<=k-2;j++)
				printf("%d ",ansE[i][j]);
			printf("%d\n",ansE[i][k-1]);
		}
	}
	
	return 0;
}
