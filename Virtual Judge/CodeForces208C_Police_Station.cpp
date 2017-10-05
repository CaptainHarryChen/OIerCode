#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const long long MAXN=105,MAXM=MAXN*MAXN/2;
struct Edge
{
	long long v;
	Edge *next;
	Edge(){}
	Edge(long long _v)
	{v=_v;next=NULL;}
};
struct Graph
{
	Edge E[MAXM*2],*V[MAXN],*cur;
	Graph(){cur=E;}
	void add_edge(long long a,long long b)
	{
		*cur=Edge(b);
		cur->next=V[a];
		V[a]=cur++;
		*cur=Edge(a);
		cur->next=V[b];
		V[b]=cur++;
	}
};
long long n,m;
Graph G;
long long lev[2][MAXN];
void BFS(long long S,long long id)
{
	queue<int> Q;
	memset(lev+1,0x3F,sizeof(int)*n);
	Q.push(S);
	lev[id][S]=1;
	while(!Q.empty())
	{
		long long t=Q.front();
		Q.pop();
		for(Edge *p=G.V[t];p;p=p->next)
			if(lev[id][p->v]>lev[id][t]+1)
			{
				lev[id][p->v]=lev[id][t]+1;
				Q.push(p->v);
			}
	}
}
long long pass[MAXN];
long long pcnt[2][MAXN];
long long DFS(long long u,long long T,long long id)
{
	if(pcnt[id][u])
		return pcnt[id][u];
	if(u==T)
		return pcnt[id][u]=1;
	long long ret=0;
	for(Edge *p=G.V[u];p;p=p->next)
		if(lev[id][p->v]==lev[id][u]+1)
		{
			long long t=DFS(p->v,T,id);
			ret+=t;
			pass[u]+=t;
			pass[p->v]+=t;
		}
	return pcnt[id][u]=ret;
}
int main()
{
	long long a,b;
	scanf("%I64d%I64d",&n,&m);
	memset(lev,0x3F,sizeof lev);
	for(long long i=1;i<=m;i++)
	{
		scanf("%I64d%I64d",&a,&b);
		G.add_edge(a,b);
	}
	BFS(1,0);
	BFS(n,1);
	DFS(1,n,0);
	DFS(n,1,1);
	long long dis=lev[0][n];
	long long  mx=0;
	for(long long i=1;i<=n;i++)
		if(lev[0][i]+lev[1][i]-1==dis)
			mx=max(mx,pcnt[0][i]*pcnt[1][i]*(i==1||i==n?1:2));
	printf("%.12lf\n",1.0*mx/pcnt[0][1]);
	return 0;
}
