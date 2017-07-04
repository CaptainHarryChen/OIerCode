#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXN=300005;
struct Edge
{
	int to,len;
	Edge *next;
	Edge(){}
	Edge(int _to,int _l){to=_to;len=_l;}
};
struct Graph
{
	Edge edges[MAXN*2],*head[MAXN],*cur;
	Graph(){cur=edges;}
	void clear(){cur=edges;}
	void add_edge(int u,int v,int len=1)
	{
		*cur=Edge(v,len);
		cur->next=head[u];
		head[u]=cur++;
		*cur=Edge(u,len);
		cur->next=head[v];
		head[v]=cur++;
	}
};
int vnode[MAXN],tot;
int size[MAXN];
namespace Vtree
{
	Graph Tr,Vtr;
	int stack[MAXN],top;
	int dfn[MAXN],dfn_id;
	int fa[MAXN][20],lev[MAXN];
	int vfa[MAXN],dis[MAXN];
	void dfs_Init(int id,int from,int level)
	{
		dfn[id]=++dfn_id;
		lev[id]=level;
		size[id]=1;
		for(Edge *p=Tr.head[id];p;p=p->next)
			if(p->to!=from)
			{
				fa[p->to][0]=id;
				dfs_Init(p->to,id,level+1);
				size[id]+=size[p->to];
			}
	}
	void Init(int n)
	{
		top=dfn_id=0;
		dfs_Init(0,-1,1);
		for(int j=1;j<20;j++)
			for(int i=0;i<=n;i++)
				if(lev[i]>(1<<j))
					fa[i][j]=fa[fa[i][j-1]][j-1];
	}
	int LCA(int a,int b)
	{
		if(lev[a]>lev[b])std::swap(a,b);
		for(int i=19;i>=0;i--)
			if(lev[b]-(1<<i)>=lev[a])
				b=fa[b][i];
		if(a==b)return a;
		for(int i=19;i>=0;i--)
			if(lev[a]>(1<<i)&&fa[a][i]!=fa[b][i])
				a=fa[a][i],b=fa[b][i];
		return fa[a][0];
	}
	bool node_cmp(int a,int b)
	{return dfn[a]<dfn[b];}
	void BuildTree(int node[],int n)
	{
		Vtr.clear();top=0;
		vfa[0]=-1;
		std::sort(node,node+n,node_cmp);
		stack[top++]=node[0];
		for(int i=1;i<n;i++)
		{
			int x=node[i],p=stack[top-1],q,lca=LCA(x,p);
			if(p==lca)
				stack[top++]=x;
			else
			{
				for(q=stack[top-2];top>=2;q=stack[top-2],p=stack[top-1])
				{
					if(dfn[q]>=dfn[lca])
					{
						vfa[p]=q;
						dis[p]=lev[p]-lev[q];
						Vtr.add_edge(q,p,lev[p]-lev[q]);
						top--;
					}
					if(dfn[q]<dfn[lca])
					{
						vfa[p]=lca;
						dis[p]=lev[p]-lev[lca];
						vnode[tot++]=lca;
						Vtr.add_edge(lca,p,lev[p]-lev[lca]);
						top--;
						stack[top++]=lca;
					}
					if(dfn[q]<=dfn[lca])
						break;
				}
				if(stack[top-1]!=lca)
				{
					vfa[p]=lca;
					dis[p]=lev[p]-lev[lca];
					vnode[tot++]=lca;
					Vtr.add_edge(lca,p,lev[p]-lev[lca]);
					top--;
					stack[top++]=lca;
				}
				stack[top++]=x;
			}
		}
		for(int i=top-2;i>=0;i--)
		{
			vfa[stack[i+1]]=stack[i];
			dis[stack[i+1]]=lev[stack[i+1]]-lev[stack[i]];
			Vtr.add_edge(stack[i],stack[i+1],lev[stack[i+1]]-lev[stack[i]]);
		}
	}
}
int key_node[MAXN],n,backup[MAXN];
int near[MAXN],neid[MAXN];
int ans[MAXN],cnt[MAXN];
void Get_near()
{
	using namespace Vtree;
	std::sort(vnode,vnode+tot,Vtree::node_cmp);
	for(int i=tot-1;i>=0;i--)
	{
		int x=vnode[i];
		if((near[vfa[x]]>near[x]+dis[x])||(near[vfa[x]]==near[x]+dis[x]&&neid[vfa[x]]>neid[x]))
			near[vfa[x]]=near[x]+dis[x],neid[vfa[x]]=neid[x];
	}
	for(int i=1;i<tot;i++)
	{
		int x=vnode[i];
		if((near[x]>near[vfa[x]]+dis[x])||(near[x]==near[vfa[x]]+dis[x]&&neid[x]>neid[vfa[x]]))
			near[x]=near[vfa[x]]+dis[x],neid[x]=neid[vfa[x]];
	}
}
void solve()
{
	using namespace Vtree;
	for(int i=0;i<tot;i++)
		cnt[vnode[i]]=size[vnode[i]];
	for(int i=0;i<tot;i++)
	{
		int x=vnode[i],fa=vfa[x],fax=x;
		for(int j=19;j>=0;j--)
			if(lev[fax]-(1<<j)>lev[fa])
				fax=Vtree::fa[fax][j];
		if(fa==0)
			ans[neid[x]]+=n-size[x];
		else
		{
			cnt[fa]-=size[fax];
			if(neid[x]==neid[fa])
				ans[neid[x]]+=size[fax]-size[x];
			else
			{
				int mid=(dis[x]+near[fa]-near[x])/2;
				if(mid+near[x]==near[fa]+dis[x]-mid&&neid[fa]<neid[x])
					mid--;
				int p=x;
				for(int j=19;j>=0;j--)
					if(lev[p]-(1<<j)>=lev[x]-mid)
						p=Vtree::fa[p][j];
				ans[neid[x]]+=size[p]-size[x];
				ans[neid[fa]]+=size[fax]-size[p];
			}
		}
	}
	for(int i=0;i<tot;i++)
		ans[neid[vnode[i]]]+=cnt[vnode[i]];
}
int main()
{
	int m,q;
	scanf("%d",&n);
	Vtree::Tr.add_edge(0,1);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		Vtree::Tr.add_edge(u,v);
	}
	Vtree::Init(n);
	scanf("%d",&q);
	memset(near,0x3F,sizeof near);
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&m);
		key_node[0]=0;
		tot=0;
		for(int j=1;j<=m;j++)
		{
			scanf("%d",key_node+j);
			backup[j]=key_node[j];
			vnode[tot++]=key_node[j];
			ans[key_node[j]]=0;
		}
		Vtree::BuildTree(key_node,m+1);
		for(int i=0;i<tot;i++)
			near[vnode[i]]=0x3F3F3F3F,neid[vnode[i]]=-1,Vtree::Vtr.head[vnode[i]]=NULL;
		for(int j=1;j<=m;j++)
			near[key_node[j]]=0,neid[key_node[j]]=key_node[j];
		Get_near();
		solve();
		for(int j=1;j<=m;j++)
			printf("%d ",ans[backup[j]]);
		printf("\n");
	}
	return 0;
}
