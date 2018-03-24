#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=100005,MAXM=MAXN*10,INF=0x3F3F3F3F;

struct Edge
{
	int v,cap,cost;
	Edge *nxt,*bck;
	Edge(){}
	Edge(int _v,int _cap,int _cost)
	{v=_v;cap=_cap;cost=_cost;nxt=bck=NULL;}
}E[MAXM],*adj[MAXN],*cur=E;
void add_edge(int u,int v,int cap,int cost)
{
	*cur=Edge(v,cap,cost);
	cur->nxt=adj[u];
	cur->bck=cur+1;
	adj[u]=cur++;
	*cur=Edge(u,0,-cost);
	cur->nxt=adj[v];
	cur->bck=cur-1;
	adj[v]=cur++;
}

int dis[MAXN],path[MAXN];
Edge *pathE[MAXN];
bool vis[MAXN];
queue<int> Q;
int aug(int S,int T,int N)
{
	memset(dis,0x3F,sizeof dis);
	memset(vis,0,sizeof vis);
	dis[S]=0;
	vis[S]=true;
	Q.push(S);
	while(!Q.empty())
	{
		int u=Q.front();
		vis[u]=false;
		Q.pop();
		for(Edge *p=adj[u];p;p=p->nxt)
			if(p->cap>0&&dis[u]+p->cost<dis[p->v])
			{
				dis[p->v]=p->cost+dis[u];
				path[p->v]=u;
				pathE[p->v]=p;
				if(!vis[p->v])
				{
					vis[p->v]=true;
					Q.push(p->v);
				}
			}
	}
	if(dis[T]==INF)
		return 0;
	int x=T,augc=INF;
	while(x!=S)
	{
		augc=min(augc,pathE[x]->cap);
		x=path[x];
	}
	x=T;
	while(x!=S)
	{
		pathE[x]->cap-=augc;
		pathE[x]->bck->cap+=augc;
		x=path[x];
	}
	return augc;
}
int Flow(int S,int T,int N)
{
	int flow=0,val=0,temp;
	while(temp=aug(S,T,N),temp!=0)
	{
		flow+=temp;
		val+=dis[T]*temp;
	}
	return val;
}

int N,p,m,f,n,s;
int need[MAXN];

int main()
{
	scanf("%d%d%d%d%d%d",&N,&p,&m,&f,&n,&s);
	for(int i=1;i<=N;i++)
		scanf("%d",need+i);
	int S=0,T=2*N+1;
	for(int i=1;i<=N;i++)
		add_edge(S,i,need[i],0);
	for(int i=1;i<=N;i++)
		add_edge(i+N,T,need[i],0);
	for(int i=1;i<N;i++)
		add_edge(i,i+1,INF,0);
	for(int i=N+1;i<=2*N;i++)
		add_edge(S,i,INF,p);
	for(int i=1;i+m<=N;i++)
		add_edge(i,i+N+m,INF,f);
	for(int i=1;i+n<=N;i++)
		add_edge(i,i+N+n,INF,s);
		
	printf("%d\n",Flow(0,T,2*N+2));
	
	return 0;
}
