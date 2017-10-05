#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=100005,MAXM=300005;
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
long long dis[MAXN];
priority_queue<State,vector<State>,greater<State> >Q;
bool used[MAXN];
int main()
{
	int a,b,c,n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	memset(dis+1,0x3F,sizeof(long long)*n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		G.add_edge(a,b,c);
	}
	int ans=0;
	for(int i=1;i<=k;i++)
	{
		scanf("%d%d",&b,&c);
		if(used[b])
			ans++;
		if(dis[b]>c)
		{
			dis[b]=c;
			Q.push(State(b,dis[b]));
		}
		used[b]=true;
	}
	Q.push(State(1,0LL));
	dis[1]=0LL;
	State t;
	while(!Q.empty())
	{
		t=Q.top();Q.pop();
		if(t.d>dis[t.u])
			continue;
		for(Edge *p=G.V[t.u];p;p=p->next)
			if(dis[p->v]>=dis[t.u]+p->len)
			{
				if(dis[p->v]>dis[t.u]+p->len)
				{
					dis[p->v]=dis[t.u]+p->len;
					Q.push(State(p->v,dis[p->v]));
				}
				if(used[p->v])
				{
					ans++;
					used[p->v]=false;
				}
			}
	}
	printf("%d\n",ans);
	return 0;
}
