#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=1005,MAXNODE=2000005,MAXEDGE=6000005;

struct Edge
{
	int v,len;
	Edge *nxt;
}edge[MAXEDGE],*adj[MAXNODE],*ecnt=edge;
void AddEdge(int u,int v,int len)
{
	ecnt->v=v;
	ecnt->len=len;
	ecnt->nxt=adj[u];
	adj[u]=ecnt++;
	ecnt->v=u;
	ecnt->len=len;
	ecnt->nxt=adj[v];
	adj[v]=ecnt++;
}

int dis[MAXNODE];
bool vis[MAXNODE];
queue<int> Q;
void SPFA(int S)
{
	memset(dis,0x3F,sizeof dis);
	dis[S]=0;
	Q.push(S);
	vis[S]=true;
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		vis[u]=false;
		for(Edge *p=adj[u];p;p=p->nxt)
		{
			int v=p->v,len=p->len;
			if(dis[v]>dis[u]+len)
			{
				dis[v]=dis[u]+len;
				if(!vis[v])
				{
					Q.push(v);
					vis[v]=true;
				}
			}
		}
	}
}

int main()
{
	int N,M;
	scanf("%d%d",&N,&M);
	if(N==1||M==1)
	{
		int ans=0x7FFFFFFF,x;
		for(int i=1;i<=N*M-1;i++)
		{
			scanf("%d",&x);
			ans=min(ans,x);
		}
		printf("%d\n",ans);
		return 0;
	}
	int S=0,T=1,u,v,len;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M-1;j++)
		{
			scanf("%d",&len);
			u=((i-1)*(M-1)+j)*2+1;
			v=((i-2)*(M-1)+j)*2;
			if(i==1)v=T;
			if(i==N)u=S;
			AddEdge(u,v,len);
		}
	for(int i=1;i<=N-1;i++)
		for(int j=1;j<=M;j++)
		{
			scanf("%d",&len);
			u=((i-1)*(M-1)+j-1)*2+1;
			v=((i-1)*(M-1)+j)*2;
			if(j==1)u=S;
			if(j==M)v=T;
			AddEdge(u,v,len);
		}
	for(int i=1;i<=N-1;i++)
		for(int j=1;j<=M-1;j++)
		{
			scanf("%d",&len);
			u=((i-1)*(M-1)+j)*2;
			v=((i-1)*(M-1)+j)*2+1;
			AddEdge(u,v,len);
		}
	
	SPFA(S);
	
	printf("%d\n",dis[T]);
	
	return 0;
}
