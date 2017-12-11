#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=10005,MAXL=10000005;

struct Edge
{
	int v,c;
	Edge *nxt;
};
Edge E[MAXN*2],*V[MAXN],*cur;
void add_edge(int u,int v,int c)
{
	cur->v=v;cur->c=c;
	cur->nxt=V[u];
	V[u]=cur++;
	cur->v=u;cur->c=c;
	cur->nxt=V[v];
	V[v]=cur++;
}

int cnt[MAXN],val[MAXN];
int vis[MAXN];
void dfs(int u,int pa=0)
{
	cnt[u]=1;
	val[u]=0;
	for(Edge *p=V[u];p;p=p->nxt)
		if(p->v!=pa&&vis[p->v]==false)
		{
			dfs(p->v,u);
			cnt[u]+=cnt[p->v];
			val[u]=max(val[u],cnt[p->v]);
		}
}
int ans,c;
void dfs2(int n,int u,int pa=0)
{
	val[u]=max(val[u],n-cnt[u]);
	if(ans>val[u])
	{
		ans=val[u];
		c=u;
	}
	for(Edge *p=V[u];p;p=p->nxt)
		if(p->v!=pa&&vis[p->v]==false)
			dfs2(n,p->v,u);
}
int find_center(int u)
{
	dfs(u);
	ans=0x7FFFFFFF;
	dfs2(cnt[u],u);
	return c;
}

int S[MAXL],id,last;
int que[MAXN],head,tail;
bool dfs3(int u,int k,int dis,int pa=0)
{
	if(k-dis<0)return false;
	if(S[k-dis]>=last&&S[k-dis]<id)return true;
	for(Edge *p=V[u];p;p=p->nxt)
		if(p->v!=pa&&vis[p->v]==false)
			if(dfs3(p->v,k,dis+p->c,u))
				return true;
	S[dis]=id;
	return false;
}
bool solve(int n,int k)
{
	memset(vis+1,0,sizeof(int)*n);
	head=tail=1;
	que[1]=1;
	while(head<=tail)
	{
		id++;
		last=id;
		S[0]=id;
		int u=que[head];
		head++;
		int g=find_center(u);
		for(Edge *p=V[g];p;p=p->nxt)
			if(vis[p->v]==false)
			{
				id++;
				if(dfs3(p->v,k,p->c,g))
					return true;
				que[++tail]=p->v;
			}
		vis[u]=true;
	}
	return false;
}

int main()
{
	int n;
	while(true)
	{
		scanf("%d",&n);
		if(n==0)break;
		cur=E;
		memset(V+1,0,sizeof(Edge*)*n);
		for(int i=1,d,c;i<=n;i++)
			while(true)
			{
				scanf("%d",&d);
				if(d==0)break;
				scanf("%d",&c);
				add_edge(i,d,c);
			}
		for(int x;;)
		{
			scanf("%d",&x);
			if(x==0)break;
			if(solve(n,x))
				puts("AYE");
			else
				puts("NAY");
		}
		puts(".");
	}
	return 0;
}
