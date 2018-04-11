#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXM=200005,MAXLOG=17;

struct Event
{
	int type;
	int a,b,lca;
	int v;
	int key;
	int id;
	bool operator < (const Event &t)const
	{return key<t.key||(key==t.key&&id<t.id);}
};
bool IdCmp(const Event &a,const Event &b)
{return a.id<b.id;}

int n,m;
int dfn[MAXN][2],dfc;
int ans[MAXM];
vector<int> adj[MAXN];
Event e[MAXM];

namespace LCA
{
	int fa[MAXN][MAXLOG+3];
	int lev[MAXN];
	void dfs(int u,int f=0,int level=1)
	{
		fa[u][0]=f;
		lev[u]=level;
		dfn[u][0]=++dfc;
		for(int i=0;i<(int)adj[u].size();i++)
			if(adj[u][i]!=f)
				dfs(adj[u][i],u,level+1);
		dfn[u][1]=dfc;
	}
	void Init()
	{
		dfs(1);
		for(int j=1;j<MAXLOG;j++)
			for(int i=1;i<=n;i++)
				fa[i][j]=fa[fa[i][j-1]][j-1];
	}
	int Query(int u,int v)
	{
		if(lev[u]>lev[v])
			swap(u,v);
		for(int j=MAXLOG-1;j>=0;j--)
			if(lev[v]-(1<<j)>=lev[u])
				v=fa[v][j];
		if(u==v)
			return u;
		for(int j=MAXLOG-1;j>=0;j--)
			if(lev[v]-(1<<j)>0&&fa[u][j]!=fa[v][j])
				u=fa[u][j],v=fa[v][j];
		return fa[u][0];
	}
}
namespace BIT
{
	int sum[MAXN],tim,ti[MAXN];
	void Add(int pos,int val)
	{
		while(pos<MAXN)
		{
			if(ti[pos]!=tim)
			{
				sum[pos]=0;
				ti[pos]=tim;
			}
			sum[pos]+=val;
			pos+=(pos&(-pos));
		}
	}
	int Get(int pos)
	{
		int val=0;
		while(pos)
		{
			if(ti[pos]!=tim)
			{
				sum[pos]=0;
				ti[pos]=tim;
			}
			val+=sum[pos];
			pos-=(pos&(-pos));
		}
		return val;
	}
}

void solve(int L,int R,int valL,int valR)
{
	if(L>=R)
		return;
	if(valL==valR)
	{
		for(int i=L;i<=R;i++)
			if(e[i].type==2)
				ans[e[i].id]=(valL==0?-1:valL);
		return;
	}
	BIT::tim++;
	int valMid=(valL+valR+1)/2,Mid=0,num=0;
	for(int i=L;i<=R;i++)
	{
		if(e[i].type==0)
		{
			if(e[i].v>=valMid)
			{
				BIT::Add(dfn[e[i].a][0],1);
				BIT::Add(dfn[e[i].b][0],1);
				BIT::Add(dfn[e[i].lca][0],-1);
				if(LCA::fa[e[i].lca][0])
					BIT::Add(dfn[LCA::fa[e[i].lca][0]][0],-1);
				e[i].key=1;
				num++;
			}
			else
				e[i].key=0,Mid++;
		}
		else if(e[i].type==1)
		{
			if(e[i].v>=valMid)
			{
				BIT::Add(dfn[e[i].a][0],-1);
				BIT::Add(dfn[e[i].b][0],-1);
				BIT::Add(dfn[e[i].lca][0],1);
				if(LCA::fa[e[i].lca][0])
					BIT::Add(dfn[LCA::fa[e[i].lca][0]][0],1);
				e[i].key=1;
				num--;
			}
			else
				e[i].key=0,Mid++;
		}
		else
		{
			int temp=BIT::Get(dfn[e[i].a][1])-BIT::Get(dfn[e[i].a][0]-1);
			if(temp<num)
				e[i].key=1;
			else
				e[i].key=0,Mid++;
		}
	}
	sort(e+L,e+R+1);
	solve(L,L+Mid-1,valL,valMid-1);
	solve(L+Mid,R,valMid,valR);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	LCA::Init();
	int mx=0;
	for(int i=1,t;i<=m;i++)
	{
		scanf("%d",&e[i].type);
		if(e[i].type==0)
		{
			scanf("%d%d%d",&e[i].a,&e[i].b,&e[i].v);
			e[i].lca=LCA::Query(e[i].a,e[i].b);
			e[i].id=i;
			mx=max(mx,e[i].v);
		}
		else if(e[i].type==1)
		{
			scanf("%d",&t);
			e[i]=e[t];
			e[i].id=i;
			e[i].type=1;
		}
		else
		{
			scanf("%d",&e[i].a);
			e[i].id=i;
		}
	}
	memset(ans,-1,sizeof ans);
	solve(1,m,0,mx);
	sort(e+1,e+m+1,IdCmp);
	for(int i=1;i<=m;i++)
		if(e[i].type==2)
			printf("%d\n",ans[i]);
	
	return 0;
}
