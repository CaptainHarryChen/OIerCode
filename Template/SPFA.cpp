#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN=505;

int n,m,s,t;
int dis[MAXN];
bool inq[MAXN];
vector<int> adj[MAXN],len[MAXN];

queue<int> Q;

void SPFA()
{
	memset(dis,0x3F,sizeof dis);
	dis[s]=0;
	Q.push(s);
	inq[s]=true;
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();inq[u]=false;
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i];
			if(dis[v]>dis[u]+len[u][i])
			{
				dis[v]=dis[u]+len[u][i];
				if(!inq[v])
				{
					Q.push(v);
					inq[v]=true;
				}
			}
		}
	}
}
int main()
{
	freopen("SPFA_data.in","r",stdin);
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
	SPFA();
	printf("%d\n",dis[t]);
	
	return 0;
}
