#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=1005,MAXM=500005;

struct Edge
{
	int v,cap;
	Edge *nxt,*bck;
	Edge(){}
	Edge(int _v,int _c)
	{v=_v;cap=_c;nxt=NULL;}
};

Edge *V[MAXN],E[MAXM*2],*cur=E;
void add_edge(int u,int v,int c)
{
	cur->v=v;cur->cap=c;
	cur->nxt=V[u];
	cur->bck=cur+1;
	V[u]=cur++;
	cur->v=u;cur->cap=0;
	cur->nxt=V[v];
	cur->bck=cur-1;
	V[v]=cur++;
}

int lev[MAXN];
Edge *it[MAXN];
void UdpLev(int S)
{
	memset(lev,-1,sizeof lev);
	queue<int>Q;
	lev[S]=0;
	Q.push(S);
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		for(Edge *p=V[u];p;p=p->nxt)
			if(lev[p->v]==-1&&p->cap>0)
			{
				lev[p->v]=lev[u]+1;
				Q.push(p->v);
			}
	}
}
int aug(int u,int T,int augc=0x7FFFFFFF)
{
	if(u==T)
		return augc;
	for(Edge *p=it[u];p;p=p->nxt)
	{
		it[u]=p;
		if(lev[p->v]==lev[u]+1&&p->cap>0)
		{
			int d=aug(p->v,T,min(p->cap,augc));
			if(d>0)
			{
				p->cap-=d;
				p->bck->cap+=d;
				return d;
			}
		}
	}
	return 0;
}
int Dinic(int n,int S,int T)
{
	int flow=0,temp;
	while(true)
	{
		UdpLev(S);
		if(lev[T]==-1)
			break;
		for(int i=1;i<=n;i++)
			it[i]=V[i];
		while(temp=aug(S,T),temp>0)
			flow+=temp;
	}
	return flow;
}

int main()
{
	freopen("Dinic_list_data.in","r",stdin);
	int n,m,u,v,c;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&c);
		add_edge(u,v,c);
	}
	printf("%d\n",Dinic(n,1,n));
	return 0;
}
