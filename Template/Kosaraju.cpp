#include<cstdio>
#include<cstring>
const int MAXN=5005,MAXM=50005;

struct Edge
{
	int v;
	Edge *nxt;
}E[MAXM*4],*adj[MAXN],*radj[MAXN],*ecnt=E;
void add_edge(int u,int v)
{
	ecnt->v=v;
	ecnt->nxt=adj[u];
	adj[u]=ecnt++;
	ecnt->v=u;
	ecnt->nxt=radj[v];
	radj[v]=ecnt++;
}

int stk[MAXN],top;
int blkid[MAXN],blkc;
bool vis[MAXN];
void dfs(int u)
{
	vis[u]=true;
	for(Edge *p=adj[u];p;p=p->nxt)
		if(!vis[p->v])
			dfs(p->v);
	stk[++top]=u;
}
void rdfs(int u)
{
	vis[u]=true;
	blkid[u]=blkc;
	for(Edge *p=radj[u];p;p=p->nxt)
		if(!vis[p->v])
			rdfs(p->v);
}

void Kosaraju(int n)
{
	for(int i=1;i<=n;i++)
		if(!vis[i])
			dfs(i);
	memset(vis+1,0,sizeof(int)*n);
	while(top)
	{
		if(!vis[stk[top]])
		{
			blkc++;
			rdfs(stk[top]);
		}
		top--;
	}
}

int cnt[MAXN];
int ans[MAXN];
int main()
{
	freopen("Kosaraju_data.in","r",stdin);
	int N,M,a,b,t;
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d%d",&a,&b,&t);
		add_edge(a,b);
		if(t==2)
			add_edge(b,a);
	}
	Kosaraju(N);
	
	for(int i=1;i<=N;i++)
		cnt[blkid[i]]++;
	int mx=0,mxid;
	for(int i=1;i<=blkc;i++)
		if(cnt[i]>mx)
			mx=cnt[i],mxid=i;
	printf("%d\n",mx);
	for(int i=1,j=0;i<=N;i++)
		if(blkid[i]==mxid)
			ans[++j]=i;
	for(int i=1;i<mx;i++)
		printf("%d ",ans[i]);
	printf("%d\n",ans[mx]);
	return 0;
}
