#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=2000005;

int N,X,Y;
vector<int> red[MAXN],blue[MAXN];
int dep[MAXN],fa[MAXN];

bool isTable(int u,int v)
{
	if(dep[u]>dep[v])
		swap(u,v);
	if(fa[v]==u||fa[fa[v]]==u||fa[u]==fa[v])
		return false;
	return true;
}

void dfs1(int u)
{
	for(auto v:blue[u])
		if(v!=fa[u])
		{
			fa[v]=u;
			dep[v]=dep[u]+1;
			dfs1(v);
		}
}
int dfs2(int u,int f=0,int step=0)
{
	step++;
	int res=dep[u];
	for(auto v:red[u])
	{
		if(v==f)
			continue;
		if(isTable(u,v))
		{
			puts("-1");
			exit(0);
		}
		res=max(res,dep[v]);
		if(dep[v]>step)
			res=max(res,dfs2(v,u,step));
	}
	return res;
}

int main()
{
	scanf("%d%d%d",&N,&X,&Y);
	for(int i=1;i<N;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		red[u].push_back(v);
		red[v].push_back(u);
	}
	for(int i=1;i<N;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		blue[u].push_back(v);
		blue[v].push_back(u);
	}
	dfs1(Y);
	int ans=dfs2(X)*2;
	printf("%d\n",ans);
	
	return 0;
}
