#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=65540;
vector<int>E[MAXN],son[MAXN];
int rd[MAXN],n;
queue<int>Q;
int A[MAXN],top;
int lev[MAXN],fa[MAXN][20],sz[MAXN];
void init()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		if(x)
		{
			rd[x]++;
			E[i].push_back(x);
		}
		while(x)
		{
			scanf("%d",&x);
			if(x)
			{
				E[i].push_back(x);
				rd[x]++;
			}
		}
	}
}
void topo()
{
	for(int i=1;i<=n;i++)
		if(rd[i]==0)
			Q.push(i);
	while(!Q.empty())
	{
		int t=Q.front();
		Q.pop();
		A[++top]=t;
		for(int i=0;i<(int)E[t].size();i++)
		{
			rd[E[t][i]]--;
			if(rd[E[t][i]]==0)
				Q.push(E[t][i]);
		}
	}
}
void extend(int x,int y)
{
	son[x].push_back(y);
	fa[y][0]=x;
	lev[y]=lev[x]+1;
	for(int i=1;i<17;i++)
		fa[y][i]=fa[fa[y][i-1]][i-1];
}
int lca(int x,int y)
{
	if(lev[x]>lev[y])swap(x,y);
	for(int i=16;i>=0;i--)
		if(lev[y]-(1<<i)>=lev[x])
			y=fa[y][i];
	if(x==y)return x;
	for(int i=16;i>=0;i--)
		if(lev[x]>=(1<<i)&&fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
void build()
{
	int lc=0;
	for(int i=top;i>0;i--)
	{
		lc=0;
		if(E[A[i]].size()>0)
			lc=E[A[i]][0];
		for(int j=1;j<(int)E[A[i]].size();j++)
			lc=lca(lc,E[A[i]][j]);
		extend(lc,A[i]);
	}
}
void dfs(int x)
{
	sz[x]=1;
	for(int i=0;i<(int)son[x].size();i++)
	{
		dfs(son[x][i]);
		sz[x]+=sz[son[x][i]];
	}
}
int main()
{
	init();
	topo();
	build();
	dfs(0);
	for(int i=1;i<=n;i++)
		printf("%d\n",sz[i]-1);
	return 0;
}
