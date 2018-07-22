#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=300005,MAXM=300005,MAXLOG=18;

struct Edge
{
	int u,v,len;
	Edge(){}
	Edge(int u,int v,int len):u(u),v(v),len(len){}
	bool operator < (const Edge &t)const
	{return len<t.len;}
};
struct AdjEdge
{
	int v,len,id;
	AdjEdge(){}
	AdjEdge(int v,int len,int id):v(v),len(len),id(id){}
};

int dsu[MAXN];
int Root(int x)
{
	if(dsu[x]==0)
		return x;
	return dsu[x]=Root(dsu[x]);
}

int n,m;
vector<AdjEdge> adj[MAXN];
bool used[MAXM];
Edge edge[MAXM];
int fa[MAXN][MAXLOG],mx[MAXN][MAXLOG],mx2[MAXN][MAXLOG],dep[MAXN];
void AddEdge(int id)
{
	adj[edge[id].u].push_back(AdjEdge(edge[id].v,edge[id].len,id));
	adj[edge[id].v].push_back(AdjEdge(edge[id].u,edge[id].len,id));
}

long long Kruskal()
{
	long long ret=0;
	for(int i=1;i<=m;i++)
	{
		int r1=Root(edge[i].u),r2=Root(edge[i].v);
		if(r1==r2)
			continue;
		dsu[r1]=r2;
		ret+=edge[i].len;
		used[i]=true;
		AddEdge(i);
	}
	return ret;
}

void dfs(int u,int f=0,int deep=1)
{
	dep[u]=deep;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i].v;
		if(v!=f)
		{
			fa[v][0]=u;
			mx[v][0]=adj[u][i].len;
			dfs(v,u,deep+1);
		}
	}
}
void LCAmx(int u,int v,int &ret,int &ret2)
{
	if(dep[u]>dep[v])
		swap(u,v);
	int tu=u,tv=v;
	ret=0;
	for(int j=MAXLOG-1;j>=0;j--)
		if(dep[v]-(1<<j)>=dep[u])
		{
			ret=max(ret,mx[v][j]);
			v=fa[v][j];
		}
	if(u!=v)
	{
		for(int j=MAXLOG-1;j>=0;j--)
			if(dep[v]-(1<<j)>0&&fa[u][j]!=fa[v][j])
			{
				ret=max(ret,max(mx[u][j],mx[v][j]));
				u=fa[u][j];
				v=fa[v][j];
			}
		ret=max(ret,max(mx[u][0],mx[v][0]));
	}
	
	u=tu;v=tv;
	ret2=0;
	for(int j=MAXLOG-1;j>=0;j--)
		if(dep[v]-(1<<j)>=dep[u])
		{
			ret2=max(ret2,mx2[v][j]);
			if(mx[v][j]<ret)
				ret2=max(ret2,mx[v][j]);
			v=fa[v][j];
		}
	if(u!=v)
	{
		for(int j=MAXLOG-1;j>=0;j--)
			if(dep[v]-(1<<j)>0&&fa[u][j]!=fa[v][j])
			{
				if(mx[u][j]<ret)
					ret2=max(ret2,mx[u][j]);
				if(mx[v][j]<ret)
					ret2=max(ret2,mx[v][j]);
				ret2=max(ret2,max(mx2[u][j],mx2[v][j]));
				u=fa[u][j];
				v=fa[v][j];
			}
		if(mx[u][0]<ret)
			ret2=max(ret2,mx[u][0]);
		if(mx[v][0]<ret)
			ret2=max(ret2,mx[v][0]);
		ret2=max(ret2,max(mx2[u][0],mx2[v][0]));
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x,y,z;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		edge[i]=Edge(x,y,z);
	}
	sort(edge+1,edge+m+1);
	long long ans=Kruskal();
	
	dfs(1);
	for(int j=1;j<MAXLOG;j++)
		for(int i=1;i<=n;i++)
			if(dep[i]-(1<<j)>0)
			{
				fa[i][j]=fa[fa[i][j-1]][j-1];
				mx[i][j]=max(mx[i][j-1],mx[fa[i][j-1]][j-1]);
				int tmp[10]={0,mx[i][j-1],mx2[i][j-1],mx[fa[i][j-1]][j-1],mx2[fa[i][j-1]][j-1]};
				sort(tmp+1,tmp+5);
				int k=4;
				for(;tmp[k]==tmp[4]&&k>0;k--);
				mx2[i][j]=tmp[k];
			}
	int delta=0x7FFFFFFF;
	for(int i=1;i<=m;i++)
		if(!used[i])
		{
			int a1,a2;
			LCAmx(edge[i].u,edge[i].v,a1,a2);
			if(a1==edge[i].len)
				a1=a2;
			if(a1==0)
				continue;
			int tmp=edge[i].len-a1;
			if(tmp>0)
				delta=min(delta,tmp);
		}
	ans+=delta;
	printf("%lld\n",ans);
	
	return 0;
}
