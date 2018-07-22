#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=1005;
typedef pair<int,int> Node;

int n,m,s,t;
vector<int> adj[MAXN],len[MAXN];

int dis[MAXN];
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
		if(a.first>dis[a.second])
			continue;
		int u=a.second;
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i];
			if(dis[v]>dis[u]+len[u][i])
			{
				dis[v]=dis[u]+len[u][i];
				Q.push(Node(dis[v],v));
			}
		}
	}
}

int main()
{
	freopen("Dijkstra_data.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		adj[a].push_back(b);
		len[a].push_back(c);
		adj[b].push_back(a);
		len[b].push_back(c);
	}
	scanf("%d%d",&s,&t);
	Dijkstra(s);
	printf("%d\n",dis[t]);
	
	return 0;
}
