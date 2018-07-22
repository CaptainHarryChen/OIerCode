#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=500005,MAXM=1000005;

struct Edge
{
	int u,v,c;
	Edge(){}
	bool operator < (const Edge &t)const
	{return c<t.c;}
};

int N,M;
vector<int> adj[MAXN];
void AddEdge(int u,int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
	//printf("                          %d<->%d\n",u,v);
}
Edge E[MAXM];

int fa[MAXN];
int id[MAXN];
bool vis[MAXN];
int Root(int x)
{
	if(fa[x]==0)
		return x;
	return fa[x]=Root(fa[x]);
}

int dis[MAXN];
queue<int> Q;
void BFS()
{
	dis[1]=0;
	Q.push(1);
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i];
			if(dis[v]==0x3F3F3F3F)
			{
				dis[v]=dis[u]+1;
				Q.push(v);
			}
		}
	}
}

int main()
{
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++)
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].c);
	sort(E+1,E+M+1);
	
	int last=1,vcnt=N;
	for(int i=2;i<=M+1;i++)
	{
		if(E[i].c!=E[i-1].c)
		{
			for(int j=last;j<i;j++)
				fa[E[j].u]=fa[E[j].v]=id[E[j].u]=id[E[j].v]=vis[E[j].u]=vis[E[j].v]=0;
			for(int j=last;j<i;j++)
			{
				int r1=Root(E[j].u),r2=Root(E[j].v);
				if(r1!=r2)
					fa[r1]=r2;
			}
			for(int j=last;j<i;j++)
			{
				if(fa[E[j].u]==0&&id[E[j].u]==0)
					id[E[j].u]=++vcnt;
				if(fa[E[j].v]==0&&id[E[j].v]==0)
					id[E[j].v]=++vcnt;
			}
			for(int j=last;j<i;j++)
			{
				if(!vis[E[j].u])
				{
					AddEdge(E[j].u,id[Root(E[j].u)]);
					vis[E[j].u]=true;
				}
				if(!vis[E[j].v])
				{
					AddEdge(E[j].v,id[Root(E[j].v)]);
					vis[E[j].v]=true;
				}
			}
			last=i;
		}
	}
	
	memset(dis,0x3F,sizeof dis);
	BFS();
	
	if(dis[N]<0x3F3F3F3F)
		printf("%d\n",dis[N]/2);
	else
		puts("-1");
	
	return 0;
}
