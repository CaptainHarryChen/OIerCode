#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=500005,MAXS=(1<<22)+10;

int n;
vector<int> son[MAXN];
int c[MAXN];

int pref[MAXN],siz[MAXN],dep[MAXN];
int dfn1[MAXN],dfn2[MAXN],dfc,id[MAXN];
int ans[MAXN],st[MAXN],mx[MAXS];

void init(int u,int deep=1)
{
	siz[u]=1;
	pref[u]=0;
	dfn1[u]=++dfc;
	id[dfc]=u;
	dep[u]=deep;
	int mx=-1;
	for(int i=0;i<(int)son[u].size();i++)
	{
		st[son[u][i]]=st[u]^(1<<c[son[u][i]]);
		init(son[u][i],deep+1);
		siz[u]+=siz[son[u][i]];
		if(mx<siz[son[u][i]])
		{
			mx=siz[son[u][i]];
			pref[u]=son[u][i];
		}
	}
	dfn2[u]=dfc;
}

void del(int u)
{
	memset(mx,0x80,sizeof mx);
}
void add(int fa,int u)
{
	for(int i=dfn1[u];i<=dfn2[u];i++)
	{
		int v=id[i];
		ans[fa]=max(ans[fa],mx[0^st[v]]+dep[v]-2*dep[fa]);
		for(int k=0;k<22;k++)
			ans[fa]=max(ans[fa],mx[(1<<k)^st[v]]+dep[v]-2*dep[fa]);
	}
	for(int i=dfn1[u];i<=dfn2[u];i++)
		mx[st[id[i]]]=max(mx[st[id[i]]],dep[id[i]]);
}
void dsu(int u)
{
	for(int i=0;i<(int)son[u].size();i++)
		if(son[u][i]!=pref[u])
		{
			dsu(son[u][i]);
			del(son[u][i]);
		}
	if(pref[u])
	{
		dsu(pref[u]);
		ans[u]=ans[pref[u]];
	}

	for(int i=0;i<(int)son[u].size();i++)
		if(son[u][i]!=pref[u])
		{
			ans[u]=max(ans[u],ans[son[u][i]]);
			add(u,son[u][i]);
		}
	ans[u]=max(ans[u],mx[0^st[u]]-dep[u]);
	for(int k=0;k<22;k++)
		ans[u]=max(ans[u],mx[(1<<k)^st[u]]-dep[u]);
	mx[st[u]]=max(mx[st[u]],dep[u]);
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=2,fa;i<=n;i++)
	{
		char ch;
		scanf("%d %c",&fa,&ch);
		c[i]=ch-'a';
		son[fa].push_back(i);
	}
	
	init(1);
	memset(mx,0x80,sizeof mx);
	dsu(1);
	
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	puts("");
	
	return 0;
}
