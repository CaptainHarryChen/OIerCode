#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=1005,MAXM=300005;
struct State
{
	int u;
	long long d;
	State(){}
	State(int _u,long long _d)
	{u=_u;d=_d;}
	bool operator > (const State &t)const
	{return d>t.d;}
};
struct Edge
{
	int v,len;
	Edge *next;
	Edge(){}
	Edge(int _v,int _len)
	{v=_v;len=_len;next=NULL;}
};
struct Graph
{
	Edge E[MAXM*2],*V[MAXN],*cur;
	Graph(){cur=E;}
	void add_edge(int a,int b,int c)
	{
		*cur=Edge(b,c);
		cur->next=V[a];
		V[a]=cur++;
		*cur=Edge(a,c);
		cur->next=V[b];
		V[b]=cur++;
	}
};
Graph G;
long long dis[MAXN][MAXN],cost[MAXN];
int texi[MAXN][2];
priority_queue<State,vector<State>,greater<State> >Q;
int n,m,x,y;
void Dijkstra1(int s)
{
	memset(dis[s]+1,0x3F,sizeof(long long)*n);
	Q.push(State(s,0LL));
	dis[s][s]=0LL;
	State t;
	while(!Q.empty())
	{
		t=Q.top();Q.pop();
		if(t.d>dis[s][t.u])
			continue;
		for(Edge *p=G.V[t.u];p;p=p->next)
			if(dis[s][p->v]>dis[s][t.u]+p->len)
			{
				dis[s][p->v]=dis[s][t.u]+p->len;
				Q.push(State(p->v,dis[s][p->v]));
			}
	}
}
void Dijkstra2()
{
	memset(cost+1,0x3F,sizeof(long long)*n);
	Q.push(State(x,0LL));
	cost[x]=0LL;
	State t;
	while(!Q.empty())
	{
		t=Q.top();Q.pop();
		if(t.d>cost[t.u])
			continue;
		for(int i=1;i<=n;i++)
			if(dis[t.u][i]<=texi[t.u][0]&&cost[i]>t.d+texi[t.u][1])
			{
				cost[i]=t.d+texi[t.u][1];
				Q.push(State(i,cost[i]));
			}
	}
}
int main()
{
	int a,b,c;
	scanf("%d%d%d%d",&n,&m,&x,&y);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		G.add_edge(a,b,c);
	}
	for(int i=1;i<=n;i++)
		Dijkstra1(i);
	for(int i=1;i<=n;i++)
		scanf("%d%d",texi[i],texi[i]+1);
	Dijkstra2();
	if(cost[y]==0x3F3F3F3F3F3F3F3FLL)
		puts("-1");
	else
		printf("%I64d\n",cost[y]);
	return 0;
}
