#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=200005,MAXM=400005;

struct Edge
{
	int v,c;
	Edge *nxt;
}E[MAXM*2],*adj[MAXN],*ncnt=E;
void add_edge(int u,int v,int c)
{
	ncnt->v=v;
	ncnt->c=c;
	ncnt->nxt=adj[u];
	adj[u]=ncnt++;
}
int n,m;
int d[MAXN];
int path[MAXN],fa[MAXN];
int q[MAXN],head,tail;
int ans[MAXN];
bool vis[MAXN];

int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		ncnt=E;
		memset(adj+1,0,sizeof(Edge)*n);
		for(int i=1,u,v,c;i<=m;i++)
		{
			scanf("%d%d%d",&u,&v,&c);
			add_edge(u,v,c);
			add_edge(v,u,c);
		}
		memset(d,-1,sizeof d);
		head=tail=1;
		q[1]=n;
		d[n]=0;
		while(head<=tail)
		{
			int u=q[head++];
			for(Edge *p=adj[u];p;p=p->nxt)
				if(d[p->v]==-1)
				{
					d[p->v]=d[u]+1;
					q[++tail]=p->v;
				}
		}
		memset(vis,0,sizeof vis);
		head=tail=1;
		q[1]=1;
		vis[1]=true;
		for(int dd=d[1];dd>0;dd--)
		{
			int mn=0x7FFFFFFF;
			for(int it=head;it<=tail;it++)
				for(Edge *p=adj[q[it]];p;p=p->nxt)
					if(d[p->v]==d[q[it]]-1)
						mn=min(mn,p->c);
			int u,ed=tail;
			while(head<=ed)
			{
				u=q[head++];
				for(Edge *p=adj[u];p;p=p->nxt)
					if(d[p->v]==d[u]-1&&p->c==mn&&!vis[p->v])
					{
						fa[p->v]=u;
						path[p->v]=mn;
						vis[p->v]=true;
						q[++tail]=p->v;
					}
			}
		}
		printf("%d\n",d[1]);
		int x=n;
		while(x!=1)
		{
			ans[d[x]]=path[x];
			x=fa[x];
		}
		for(int i=d[1]-1;i>0;i--)
			printf("%d ",ans[i]);
		printf("%d\n",ans[0]);
	}
	return 0;
}
