#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=3005;
const long long LLF=0x3F3F3F3F3F3F3F3FLL;
typedef pair<long long,int> Node;

int n,m,s,t;
vector<int> adj[MAXN],len[MAXN],pro[MAXN];
int deg[MAXN];
bool vis[MAXN];

long long dis[MAXN],ti[MAXN];
priority_queue< Node,vector<Node>,greater<Node> > Q;

void Dijkstra(int S)
{
	memset(dis,0x3F,sizeof dis);
	dis[S]=0;
	Q.push(Node(0,S));
	while(!Q.empty())
	{
		Node a=Q.top();
		Q.pop();
		int u=a.second;
		if(vis[u])
			continue;
		vis[u]=true;
		a.first=max(dis[u],ti[u]);
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i];
			if(dis[v]>a.first+len[u][i])
			{
				dis[v]=a.first+len[u][i];
				if(deg[v]==0)
					Q.push(Node(max(dis[v],ti[v]),v));
			}
		}
		for(int j=0;j<(int)pro[u].size();j++)
		{
			int v=pro[u][j];
			deg[v]--;
			ti[v]=max(ti[v],max(dis[u],ti[u]));
			if(deg[v]==0)
				Q.push(Node(max(dis[v],ti[v]),v));
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		adj[a].push_back(b);
		len[a].push_back(c);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",deg+i);
		for(int j=1,k;j<=deg[i];j++)
		{
			scanf("%d",&k);
			pro[k].push_back(i);
		}
	}
	Dijkstra(1);
	printf("%lld\n",max(dis[n],ti[n]));
	
	return 0;
}
