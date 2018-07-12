#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=105,MAXM=23,INF=100000000;

struct Edge
{
	int v,len;
	Edge(int a,int b):v(a),len(b){}
};

vector<Edge> adj[MAXM];
bool able[MAXM][MAXN],use[MAXM];
long long dis[MAXN][MAXN][MAXM];
bool inq[MAXM];
queue<int> Q;

void SPFA(int a,int b)
{
	fill(dis[a][b],dis[a][b]+MAXM,INF);
	fill(inq,inq+MAXM,0);
	dis[a][b][1]=0;
	Q.push(1);
	inq[1]=true;
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		inq[u]=false;
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i].v,len=adj[u][i].len;
			if(!use[v])
				continue;
			if(dis[a][b][v]>dis[a][b][u]+len)
			{
				dis[a][b][v]=dis[a][b][u]+len;
				if(!inq[v])
				{
					Q.push(v);
					inq[v]=true;
				}
			}
		}
	}
}

long long dp[MAXN];

int main()
{
	int n,m,K,e,d;
	scanf("%d%d%d%d",&n,&m,&K,&e);
	for(int i=1,u,v,len;i<=e;i++)
	{
		scanf("%d%d%d",&u,&v,&len);
		adj[u].push_back(Edge(v,len));
		adj[v].push_back(Edge(u,len));
	}
	scanf("%d",&d);
	for(int i=1,P,a,b;i<=d;i++)
	{
		scanf("%d%d%d",&P,&a,&b);
		for(int j=a;j<=b;j++)
			able[P][j]=true;
	}
	for(int a=1;a<=n;a++)
	{
		fill(use,use+MAXM,true);
		for(int b=a;b<=n;b++)
		{
			for(int k=1;k<=m;k++)
				if(able[k][b])
					use[k]=false;
			SPFA(a,b);
		}
	}
	
	fill(dp,dp+MAXN,INF);
	dp[0]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			dp[i]=min(dp[i],dp[j-1]+1LL*dis[j][i][m]*(i-j+1)+K);
	
	printf("%lld\n",dp[n]-K);
	
	return 0;
}
