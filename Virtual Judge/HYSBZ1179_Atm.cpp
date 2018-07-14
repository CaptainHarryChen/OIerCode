#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=500005;

template<class T> void Read(T &x)
{
	char c;
	bool f=0;
	while(c=getchar(),c!=EOF)
	{
		if(c=='-')
			f=1;
		else if(c>='0'&&c<='9')
		{
			x=c-'0';
			while(c=getchar(),c>='0'&&c<='9')
				x=x*10+c-'0';
			if(f)
				x=-x;
			return;
		}
	}
}

struct Edge
{
	int v;
	Edge *nxt;
}edge[MAXN*2],*adj[MAXN],*adj2[MAXN],*ecnt=edge;

void AddEdge1(int u,int v)
{ecnt->v=v;ecnt->nxt=adj[u];adj[u]=ecnt++;}
void AddEdge2(int u,int v)
{ecnt->v=v;ecnt->nxt=adj2[u];adj2[u]=ecnt++;}

int N,M;
int val[MAXN],val2[MAXN];

int dfn[MAXN],low[MAXN],dfc;
int stk[MAXN],tp;
bool anc[MAXN];
int blkid[MAXN],blkc;

void tarjan(int u)
{
	dfn[u]=++dfc;
	low[u]=dfn[u];
	anc[u]=true;
	stk[++tp]=u;
	for(Edge *p=adj[u];p;p=p->nxt)
	{
		int v=p->v;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(anc[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		blkc++;
		do
		{
			blkid[stk[tp]]=blkc;
			anc[stk[tp]]=false;
			val2[blkc]+=val[stk[tp]];
			tp--;
		}while(tp>0&&stk[tp+1]!=u);
	}
}
void BuildGraph()
{
	for(int u=1;u<=N;u++)
		for(Edge *p=adj[u];p;p=p->nxt)
		{
			int v=p->v;
			if(blkid[u]==blkid[v])
				continue;
			AddEdge2(blkid[u],blkid[v]);
		}
}

queue<int> Q;
int dis[MAXN];
bool inq[MAXN];
void SPFA(int S)
{
	memset(dis,0x80,sizeof dis);
	Q.push(S);
	dis[S]=val2[S];
	inq[S]=true;
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		inq[u]=false;
		for(Edge *p=adj2[u];p;p=p->nxt)
		{
			int v=p->v;
			if(dis[v]<dis[u]+val2[v])
			{
				dis[v]=dis[u]+val2[v];
				if(!inq[v])
				{
					Q.push(v);
					inq[v]=false;
				}
			}
		}
	}
}

int main()
{
	Read(N);Read(M);
	for(int i=1;i<=M;i++)
	{
		int x,y;
		Read(x);Read(y);
		AddEdge1(x,y);
	}
	for(int i=1;i<=N;i++)
		Read(val[i]);
	int S,P;	
	Read(S);Read(P);
	
	for(int i=1;i<=N;i++)
		if(dfn[i]==0)
			tarjan(i);
	BuildGraph();
	S=blkid[S];
	
	SPFA(S);
	int ans=0;
	for(int i=1,p;i<=P;i++)
	{
		Read(p);
		ans=max(ans,dis[blkid[p]]);
	}
	
	printf("%d\n",ans);
	
	return 0;
}
