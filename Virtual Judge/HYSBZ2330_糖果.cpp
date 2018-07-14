#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const long long MAXN=100005;

long long N,K;

long long dis[MAXN],cnt[MAXN];
bool inq[MAXN];
vector<long long> adj[MAXN],len[MAXN];

void AddEdge(long long u,long long v,long long l)
{
	adj[u].push_back(v);
	len[u].push_back(l);
}

queue<long long> Q;

long long SPFA(long long S)
{
	fill(dis+1,dis+N+1,-0x3F3F3F3F);
	dis[S]=0;
	Q.push(S);
	inq[S]=true;
	while(!Q.empty())
	{
		long long u=Q.front();
		Q.pop();
		inq[u]=false;
		cnt[u]++;
		if(cnt[u]>=N)
			return -1;
		for(long long i=0;i<(long long)adj[u].size();i++)
		{
			long long v=adj[u][i];
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
	long long res=0;
	for(long long i=0;i<=N;i++)
		res+=dis[i];
	return res;
}
int main()
{
	long long X,A,B;
	scanf("%lld%lld",&N,&K);
	for(long long i=1;i<=K;i++)
	{
		scanf("%lld%lld%lld",&X,&A,&B);
		switch(X)
		{
			case 1:
				AddEdge(A,B,0);
				AddEdge(B,A,0);
				break;
			case 2:
				AddEdge(A,B,1);
				if(A==B)
				{
					puts("-1");
					return 0;
				}
				break;
			case 3:
				AddEdge(B,A,0);
				break;
			case 4:
				AddEdge(B,A,1);
				if(A==B)
				{
					puts("-1");
					return 0;
				}
				break;
			case 5:
				AddEdge(A,B,0);
				break;
		}
	}
	for(long long i=1;i<=N;i++)
		AddEdge(0,i,1);
	
	printf("%lld\n",SPFA(0));
	
	return 0;
}
