#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXM=1000005;
struct Edge
{
	int v;
	bool vis;
	Edge *next,*back;
};
Edge E[MAXM*2],*V[MAXN],*cur=E;
void add_edge(int u,int v)
{
	cur->v=v;
	cur->vis=false;
	cur->back=cur+1;
	cur->next=V[u];
	V[u]=cur++;
	cur->v=u;
	cur->vis=false;
	cur->back=cur-1;
	cur->next=V[v];
	V[v]=cur++;
}
int dfn[MAXN],low[MAXN],dfc;
int blkc,maxblk;
pair<int,int>stack[MAXN];int top;
pair<int,int>ans[MAXN],tmp[MAXN];
bool check(int x,int y)
{
	int sz=(y-x+1);
	memcpy(tmp+1,stack+x,sizeof(pair<int,int>)*sz);
	for(int i=1;i<=sz;i++)
		if(tmp[i].first>tmp[i].second)
			swap(tmp[i].first,tmp[i].second);
	sort(tmp+1,tmp+sz+1);
	for(int i=1;i<=sz;i++)
		if(stack[i]<ans[i])
			return true;
		else if(stack[i]>ans[i])
			return false;
	return false;
}
void dfs(int u,int fa)
{
	dfn[u]=low[u]=++dfc;
	for(Edge *p=V[u];p;p=p->next)
	{
		if(p->vis)
			continue;
		int v=p->v;
		p->vis=true;
		p->back->vis=true;
		stack[++top]=make_pair(u,v);
		if(!dfn[v])
		{
			dfs(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u])
			{
				int sz=0,x;
				blkc++;
				for(x=top;x&&(stack[x].first!=u||stack[x].second!=v);x--);
				sz=top-x+1;
				if(sz>maxblk||(sz==maxblk&&check(x,top)))
				{
					maxblk=sz;
					memcpy(ans+1,stack+x,sizeof(pair<int,int>)*sz);
					for(int i=1;i<=maxblk;i++)
						if(ans[i].first>ans[i].second)
							swap(ans[i].first,ans[i].second);
					sort(ans+1,ans+maxblk+1);
				}
				top=x-1;
			}
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
}
int main()
{
	int n,m,u,v;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i,-1);
	printf("%d\n%d\n",blkc,maxblk);
	for(int i=1;i<=maxblk;i++)
		printf("%d %d\n",ans[i].first,ans[i].second);
	return 0;
}
