#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=5005,MAXM=50005;

struct Edge
{
	int v;
	Edge *nxt;
}E[MAXM*4],*adj[MAXN],*ecnt=E;
void add_edge(int u,int v)
{
	ecnt->v=v;
	ecnt->nxt=adj[u];
	adj[u]=ecnt++;
}

int dfn[MAXN],dfc,low[MAXN];
int stk[MAXN],top;
int blkid[MAXN],blkc;
bool ind[MAXN];
void tarjan(int u,int fa)
{
	dfn[u]=++dfc;
	low[u]=dfn[u];
	ind[u]=true;
	stk[++top]=u;
	for(Edge *p=adj[u];p;p=p->nxt)
	{
		int v=p->v;
		if(!dfn[v])
		{
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}
		else if(ind[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		blkc++;
		do
		{
			blkid[stk[top]]=blkc;
			ind[stk[top]]=false;
			top--;
		}while(stk[top+1]!=u);
	}
}

int cnt[MAXN];
int ans[MAXN];
int main()
{
	freopen("tarjan-directed_data.in","r",stdin);
	int N,M,a,b,t;
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d%d",&a,&b,&t);
		add_edge(a,b);
		if(t==2)
			add_edge(b,a);
	}
	for(int i=1;i<=N;i++)
		if(!dfn[i])
			tarjan(i,0);
	
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
