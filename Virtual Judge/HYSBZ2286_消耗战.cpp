#include<cstdio>
#include<algorithm>
const int MAXN=500005;
struct Edge
{
	int to,len;
	Edge *nxt;
	Edge(){}
	Edge(int _t,int _l){to=_t;len=_l;nxt=NULL;}	
};
Edge edges[MAXN<<1],*E[MAXN],*cur=edges;
void AddEdge(Edge *E[],Edge *&cur,int u,int v,int l)
{
	*cur=Edge(v,l);
	cur->nxt=E[u];
	E[u]=cur;
	cur++;
	*cur=Edge(u,l);
	cur->nxt=E[v];
	E[v]=cur;
	cur++;
}
long long dis[MAXN];
int dfn[MAXN],dfnn=0;
namespace LCA
{
	int n;
	int fa[MAXN][20],lev[MAXN];
	void Init(int _n)
	{
		n=_n;
		for(int j=1;j<20;j++)
			for(int i=1;i<=n;i++)
				if(lev[i]>(1<<j))
					fa[i][j]=fa[fa[i][j-1]][j-1];
	}
	int Query(int a,int b)
	{
		if(lev[a]>lev[b])
			std::swap(a,b);
		for(int i=19;i>=0;i--)
			if(lev[b]-(1<<i)>=lev[a])
				b=fa[b][i];
		if(a==b)return a;
		for(int i=19;i>=0;i--)
			if(lev[a]>(1<<i)&&fa[a][i]!=fa[b][i])
				a=fa[a][i],b=fa[b][i];
		return fa[a][0];
	}
}
namespace VT
{
	int stack[MAXN],top;
	Edge edges[MAXN<<1],*node[MAXN],*cur;
	bool vnode_cmp(int a,int b)
	{return dfn[a]<dfn[b];}
	void BuildTree(int vnode[],int n)
	{
		std::sort(vnode,vnode+n,vnode_cmp);
		top=0;
		cur=edges;
		stack[top++]=vnode[0];
		for(int i=1;i<n;i++)
		{
			int x=vnode[i],p=stack[top-1];
			int lca=LCA::Query(p,x);
			if(lca==p)
				stack[top++]=x;
			else
			{
				int q=top-1;
				while(q>=0&&LCA::lev[stack[q]]>LCA::lev[lca])q--;
				q++;
				for(int j=q;j<top-1;j++)
					AddEdge(node,cur,stack[j],stack[j+1],0);
				int _q=stack[q];
				if(q==0)
					stack[0]=lca,top=1;
				else if(stack[q-1]!=lca)
					stack[q]=lca,top=q+1;
				else
					top=q;
				AddEdge(node,cur,_q,lca,0);
				node[x]=NULL;
				stack[top++]=x;
			}
		}
		for(int j=0;j<top-1;j++)
			AddEdge(node,cur,stack[j],stack[j+1],0);
	}
}
void DFS_init(int now,int la=0,int level=1)
{
	using namespace VT;
	using namespace LCA;
	dfn[now]=++dfnn;
	lev[now]=level;
	if(la==0)dis[now]=0x7FFFFFFFFFFFFFFFLL;
	for(Edge *p=E[now];p;p=p->nxt)
		if(p->to!=la)
		{
			fa[p->to][0]=now;
			dis[p->to]=std::min((long long)p->len,dis[now]);
			DFS_init(p->to,now,level+1);
		}
}
bool has_res[MAXN];
int res[MAXN];
long long DP(int id,int la=0)
{
	using namespace VT;
	long long ret=0;
	for(Edge *p=node[id];p;p=p->nxt)
		if(p->to!=la)
		{
			long long temp=DP(p->to,id);
			if(has_res[p->to])
				ret+=dis[p->to];
			else
				ret+=std::min(dis[p->to],temp);
		}
	node[id]=NULL;
	return ret;
}
int main()
{
	int n,m,u,v,l,k;
    scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&u,&v,&l);
		AddEdge(E,cur,u,v,l);
	}
	DFS_init(1);
	LCA::Init(n);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&k);
		res[0]=1;
		for(int j=1;j<=k;j++)
		{
			scanf("%d",res+j);
			has_res[res[j]]=1;
		}
		k++;
		VT::BuildTree(res,k);
		printf("%lld\n",DP(1));
		for(int j=1;j<=k;j++)
			has_res[res[j]]=0;
	}
	return 0;
}
