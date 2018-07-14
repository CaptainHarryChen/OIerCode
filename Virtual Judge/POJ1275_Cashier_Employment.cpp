#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=50;

int N,K;

int dis[MAXN];
int cnt[MAXN];
bool inq[MAXN];
vector<int> adj[MAXN],len[MAXN];

void AddEdge(int u,int v,int l)
{
	adj[u].push_back(v);
	len[u].push_back(l);
	//printf("%d %d %d\n",u,v,l);
}

queue<int> Q;

int SPFA(int S,int T)
{
	fill(dis+1,dis+T+1,-0x3F3F3F3F3F3F3F3FLL);
	fill(cnt,cnt+MAXN,0);
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

int R[MAXN],cas[MAXN];

int main()
{
	//freopen("data.out","w",stdout);
	int T,N;
	scanf("%d",&T);
	while(T--)
	{
		fill(cas,cas+MAXN,0);
		fill(R,R+MAXN,0);
		for(int i=1;i<=24;i++)
			scanf("%d",&R[i]);
		scanf("%d",&N);
		for(int i=1,x;i<=N;i++)
		{
			scanf("%d",&x);
			cas[x+1]++;
		}
		int ans=-1;
		for(int s=0;s<=N;s++)
		{
			for(int i=0;i<=24;i++)
			{
				adj[i].clear();
				len[i].clear();
			}
			for(int i=1;i<=8;i++)
				AddEdge(i+16,i,R[i]-s);
			for(int i=9;i<=24;i++)
				AddEdge(i-8,i,R[i]);
			for(int i=1;i<=24;i++)
			{
				AddEdge(i-1,i,0);
				AddEdge(i,i-1,-cas[i]);
			}
			AddEdge(0,24,s);
			ans=SPFA(0,24);
			if(ans==s)
				break;
			ans=-1;
		}
		if(ans==-1)
			puts("No Solution");
		else
			printf("%d\n",ans);
	}
	
	return 0;
}
