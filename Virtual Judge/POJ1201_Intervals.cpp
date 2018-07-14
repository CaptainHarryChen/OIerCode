#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=50005;

int N,K;

long long dis[MAXN];
int cnt[MAXN];
bool inq[MAXN];
vector<int> adj[MAXN],len[MAXN];

void AddEdge(int u,int v,int l)
{
	adj[u].push_back(v);
	len[u].push_back(l);
}

queue<int> Q;

long long SPFA(int S,int T)
{
	fill(dis+1,dis+T+1,-0x3F3F3F3F3F3F3F3FLL);
	dis[S]=0;
	Q.push(S);
	inq[S]=true;
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		inq[u]=false;
		cnt[u]++;
		if(cnt[u]>T-S+1)
			return -1;
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i];
			if(dis[v]<dis[u]+len[u][i])
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
	return dis[T];
}

vector<int> node;

int main()
{
	int N,mx=0,mn=MAXN;
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		b++;
		AddEdge(a,b,c);
		mx=max(mx,b);
		mn=min(mn,a);
		node.push_back(a);
		node.push_back(b);
	}
	sort(node.begin(),node.end());
	node.resize(unique(node.begin(),node.end())-node.begin());
	for(int i=0;i<(int)node.size()-1;i++)
	{
		AddEdge(node[i+1],node[i],node[i]-node[i+1]);
		AddEdge(node[i],node[i+1],0);
	}
	printf("%lld\n",SPFA(mn,mx));
	
	return 0;
}
