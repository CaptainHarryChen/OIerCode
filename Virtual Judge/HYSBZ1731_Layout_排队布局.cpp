#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=1005;

int N,ML,MD;

int dis[MAXN],cnt[MAXN];
bool inq[MAXN];
vector<int> adj[MAXN],len[MAXN];

void AddEdge(int u,int v,int l)
{
	adj[u].push_back(v);
	len[u].push_back(l);
}

queue<int> Q;

int SPFA()
{
	fill(dis+1,dis+N+1,0x3F3F3F3F);
	dis[1]=0;
	Q.push(1);
	inq[1]=true;
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		inq[u]=false;
		cnt[u]++;
		if(cnt[u]>=N)
			return -1;
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
	if(dis[N]==0x3F3F3F3F)
		return -2;
	return dis[N];
}

int main()
{
	int A,B,D;
	scanf("%d%d%d",&N,&ML,&MD);
	for(int i=1;i<=ML;i++)
	{
		scanf("%d%d%d",&A,&B,&D);
		AddEdge(A,B,D);
	}
	for(int i=1;i<=MD;i++)
	{
		scanf("%d%d%d",&A,&B,&D);
		AddEdge(B,A,-D);
	}
	printf("%d\n",SPFA());
	
	return 0;
}
