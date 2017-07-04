#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define MAXN 10005
#define MAXM 20005
struct Edge
{
	int id,len,cos;
	int nxt;
	Edge(){}
	Edge(int i,int l,int c){id=i;len=l;cos=c;}
}E[2*MAXM];
int V[MAXN],cur;
void add_edge(int u,int v,int length,int cost)
{
	E[cur]=Edge(v,length,cost);
	E[cur].nxt=V[u];
	V[u]=cur;
	cur++;
	E[cur]=Edge(u,length,cost);
	E[cur].nxt=V[v];
	V[v]=cur;
	cur++;
}
int N,M;
int dis[MAXN],cost[MAXN];
bool inque[MAXN];
queue<int>Q;
int SPFA()
{
	memset(inque,0,sizeof inque);
	for(int i=1;i<=N;i++)
		dis[i]=cost[i]=0x3FFFFFFF;
	while(!Q.empty())
		Q.pop();
	Q.push(1);
	dis[1]=0;
	inque[1]=1;
	cost[1]=0;
	while(!Q.empty())
	{
		int t=Q.front();
		Q.pop();
		inque[t]=0;
		for(int p=V[t];p!=-1;p=E[p].nxt)
		{
			int to=E[p].id;
			int len=E[p].len;
			if(dis[to]>dis[t]+len||(dis[to]==dis[t]+len&&cost[to]>E[p].cos))
			{
				dis[to]=dis[t]+len;
				cost[to]=E[p].cos;
				if(!inque[to])
				{
					Q.push(to);
					inque[to]=1;
				}
			}
		}
	}
	int ret=0;
	for(int i=1;i<=N;i++)
		ret+=cost[i];
	return ret;
}
int main()
{
	int u,v,d,c;
	while(~scanf("%d%d",&N,&M))
	{
		if(!N&&!M)break;
		memset(V,-1,sizeof V);
		cur=0;
		for(int i=1;i<=M;i++)
		{
			scanf("%d%d%d%d",&u,&v,&d,&c);
			add_edge(u,v,d,c);
		}
		printf("%d\n",SPFA());
	}
	return 0;
}
