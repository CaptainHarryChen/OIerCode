#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=3005,MAXM=3005;
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
Graph G;
int dis[MAXN][MAXN];
queue<int>Q;
void BFS(int s)
{
	dis[s][s]=0;
	Q.push(s);
	while(!Q.empty())
	{
		int t=Q.front();
		Q.pop();
		for(Edge *p=G.V[t];p;p=p->next)
			if(dis[s][p->v]>dis[s][t]+1)
			{
				dis[s][p->v]=dis[s][t]+1;
				Q.push(p->v);
			}
	}
}
int main()
{
	int n,m,a,b,s1,t1,l1,s2,t2,l2;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		G.add_edge(a,b);
	}
	scanf("%d%d%d%d%d%d",&s1,&t1,&l1,&s2,&t2,&l2);
	for(int i=1;i<=n;i++)
	{
		memset(dis[i]+1,0x3F,sizeof(int)*n);
		BFS(i);
	}
	if(dis[s1][t1]>l1||dis[s2][t2]>l2)
	{
		puts("-1");
		return 0;
	}
	int ans=m-dis[s1][t1]-dis[s2][t2];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(dis[s1][i]+dis[i][j]+dis[j][t1]<=l1
				&&dis[s2][i]+dis[i][j]+dis[j][t2]<=l2)
				ans=max(ans,m-(dis[s1][i]+dis[j][t1]+dis[s2][i]+dis[j][t2]+dis[i][j]));
			if(dis[s1][i]+dis[i][j]+dis[j][t1]<=l1
				&&dis[s2][j]+dis[j][i]+dis[i][t2]<=l2)
				ans=max(ans,m-(dis[s1][i]+dis[j][t1]+dis[s2][j]+dis[i][t2]+dis[i][j]));
		}
	printf("%d\n",ans);
	return 0;
}
