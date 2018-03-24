#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=100005;

int n;
int c[MAXN];
vector<int> adj[MAXN];

int siz[MAXN];
int dfn1[MAXN],dfn2[MAXN],dfc;
int col[MAXN],son[MAXN];
long long ans[MAXN];

void init(int u,int fa=0)
{
	siz[u]=1;
	dfn1[u]=++dfc;
	col[dfc]=c[u];
	int mx=0;
	for(int i=0;i<(int)adj[u].size();i++)
		if(adj[u][i]!=fa)
		{
			init(adj[u][i],u);
			siz[u]+=siz[adj[u][i]];
			if(siz[adj[u][i]]>mx)
				mx=siz[adj[u][i]],son[u]=adj[u][i];
		}
	dfn2[u]=dfc;
}

long long res[MAXN];
int cnt[MAXN],mx;
void add(int u)
{
	for(int i=dfn1[u];i<=dfn2[u];i++)
	{
		cnt[col[i]]++;
		res[cnt[col[i]]]+=col[i];
		mx=max(mx,cnt[col[i]]);
	}
}
void del(int u)
{
	for(int i=dfn1[u];i<=dfn2[u];i++)
	{
		res[cnt[col[i]]]-=col[i];
		if(cnt[col[i]]==mx)
			while(res[mx]==0&&mx)
				mx--;
		cnt[col[i]]--;
	}
}
void dsu(int u,int fa=0)
{
	for(int i=0;i<(int)adj[u].size();i++)
		if(adj[u][i]!=fa&&adj[u][i]!=son[u])
		{
			dsu(adj[u][i],u);
			del(adj[u][i]);
		}
	if(son[u])
		dsu(son[u],u);
	for(int i=0;i<(int)adj[u].size();i++)
		if(adj[u][i]!=fa&&adj[u][i]!=son[u])
			add(adj[u][i]);
	cnt[c[u]]++;
	res[cnt[c[u]]]+=c[u];
	mx=max(mx,cnt[c[u]]);
	ans[u]=res[mx];
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",c+i);
	for(int i=1,x,y;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	
	init(1);
	dsu(1);
	
	for(int i=1;i<=n;i++)
		printf("%I64d ",ans[i]);
	puts("");
	
	return 0;
}
