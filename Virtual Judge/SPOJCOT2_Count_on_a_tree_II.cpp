#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
const int MAXN=500010;
int n,m,unit;
int val[MAXN],temp[MAXN];
struct Edge
{
	int to,next;
}edges[MAXN*2];
struct Question
{
	int u,v,id,l,r;
	bool operator < (const Question &t)const
	{return l!=t.l?l<t.l:r<t.r;}
}Q[MAXN*2];
int cur,G[MAXN];
int lev[MAXN],lfa[MAXN][21];
int	uni[MAXN],que[MAXN],ans[MAXN];
int cnt,top,tag;
int cnts[MAXN],vis[MAXN];
void add_edge(int u,int v)
{
	edges[cur]=(Edge){v,G[u]};G[u]=cur++;
}
int dfs(int id)
{
	int num=0;
	for(int p=G[id];~p;p=edges[p].next)
	{
		int u=edges[p].to;
		if(!lev[u])
		{
			lfa[u][0]=id;
			lev[u]=lev[id]+1;
			num+=dfs(u);
			if(num>=unit)
			{
				while(num--)uni[que[--top]]=tag;
				tag++;
			}
		}
	}
	que[top++]=id;
	return num+1;
}
int LCA(int a,int b)
{
	if(lev[a]>lev[b])std::swap(a,b);
	int d=lev[b]-lev[a];
	for(int j=0;(d>>j)!=0;j++)
		if((d>>j)&1)
			b=lfa[b][j];
	if(a==b)return a;
	for(int j=20;j>=0;j--)
		if(lfa[a][j]!=lfa[b][j])
			a=lfa[a][j],b=lfa[b][j];
	return lfa[a][0];
}
void Move(int &u)
{
	if(vis[u])
	{if(--cnts[val[u]]==0)cnt--;}
	else if(++cnts[val[u]]==1)cnt++;
	vis[u]^=1;
	u=lfa[u][0];
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{scanf("%d",&val[i]);temp[i]=val[i];}
	std::sort(temp+1,temp+n+1);
	for(int i=1;i<=n;i++)
		val[i]=std::lower_bound(temp+1,temp+n+1,val[i])-temp;
	int a,b;
	cur=0;
	memset(G,-1,sizeof G);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add_edge(a,b);
		add_edge(b,a);
	}
	unit=(int)sqrt(n);
	lev[1]=1;
	dfs(1);
	while(top)uni[que[--top]]=tag;
	for(int j=1;(1<<j)<=n;j++)
		for(int i=1;i<=n;i++)
			lfa[i][j]=lfa[lfa[i][j-1]][j-1];
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&Q[i].u,&Q[i].v);
		if(uni[Q[i].u]>uni[Q[i].v])
			std::swap(Q[i].u,Q[i].v);
		Q[i].id=i;Q[i].l=uni[Q[i].u];Q[i].r=uni[Q[i].v];
	}
	std::sort(Q+1,Q+m+1);
	int nowu=1,nowv=1;
	for(int i=1;i<=m;i++)
	{
		int du=Q[i].u,dv=Q[i].v;
		int lca=LCA(nowu,du);
		while(nowu!=lca)Move(nowu);
		while(du!=lca)Move(du);
		lca=LCA(nowv,dv);
		while(nowv!=lca)Move(nowv);
		while(dv!=lca)Move(dv);
		nowu=Q[i].u,nowv=Q[i].v;
		lca=LCA(nowu,nowv);
		ans[Q[i].id]=cnt+(!cnts[val[lca]]);
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
