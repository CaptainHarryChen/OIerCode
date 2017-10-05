#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=100005,MAXM=200005;
struct Edge
{
	int v;
	Edge *next;
	Edge(){}
	Edge(int _v)
	{v=_v;next=NULL;}
};
struct Graph
{
	Edge E[MAXM*2],*V[MAXN],*cur;
	Graph(){cur=E;}
	void add_edge(int a,int b)
	{
		*cur=Edge(b);
		cur->next=V[a];
		V[a]=cur++;
		*cur=Edge(a);
		cur->next=V[b];
		V[b]=cur++;
	}
};
struct State
{
	int u,d;
	State(){}
	State(int a,int b)
	{u=a;d=b;}
	bool operator < (const State &t)const
	{return d>t.d;}
};
Graph G;
bool vol[MAXN];
int dis[MAXN];
priority_queue<State>Q;
bool check(int S,int T,int P)
{
	while(!Q.empty())
		Q.pop();
	Q.push(State(S,0));
	dis[S]=0;
	while(!Q.empty())
	{
		State t=Q.top();
		Q.pop();
		if(dis[t.u]<t.d)
			continue;
		for(Edge *p=G.V[t.u];p;p=p->next)
		{
			if(t.d+1==P&&vol[p->v]==false)
				continue;
			if(dis[p->v]>(vol[p->v]?0:t.d+1))
			{
				dis[p->v]=vol[p->v]?0:t.d+1;
				if(p->v==T)
					return true;
				Q.push(State(p->v,dis[p->v]));
			}
		}
	}
	return false;
}
int main()
{
	int n,m,k,a,b,s,t;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&a);
		vol[a]=true;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		G.add_edge(a,b);
	}
	scanf("%d%d",&s,&t);
	vol[t]=true;
	int L=1,R=n+1,mid;
	while(L<R)
	{
		mid=(L+R)/2;
		memset(dis+1,0x3F,sizeof(int)*n);
		if(check(s,t,mid))
			R=mid;
		else
			L=mid+1;
	}
	if(L==n+1)
		puts("-1");
	else
		printf("%d\n",L);
	return 0;
}
