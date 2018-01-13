#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int MAXN=100005;

int n,m;
int adj[MAXN][100];
bool vis[MAXN];
bool nadj[100][100];

int blkid[MAXN],blkc;
vector<int>cont[100];
int st[100],ed[100],ideg[100],odeg[100];

bool mark_blk(int u)
{
	blkc++;
	if(blkc>=100)
		return false;
	cont[blkc].clear();
	blkid[u]=blkc;
	st[blkc]=u;
	vis[u]=true;
	cont[blkc].push_back(u);
	while(adj[u][0]==1&&!vis[adj[u][1]])
	{
		u=adj[u][1];
		cont[blkc].push_back(u);
		vis[u]=true;
		blkid[u]=blkc;
	}
	ed[blkc]=u;
	for(int i=1;i<=adj[u][0];i++)
		if(!vis[adj[u][i]])
			if(!mark_blk(adj[u][i]))return false;
	return true;
}
void make_new_graph()
{
	for(int i=1;i<=blkc;i++)
		ideg[i]=odeg[i]=0;
	memset(nadj,0,sizeof nadj);
	for(int i=1;i<=blkc;i++)
	{
		int u=ed[i];
		for(int j=1;j<=adj[u][0];j++)
		{
			int v=adj[u][j];
			if(st[blkid[v]]==v)
			{
				nadj[i][blkid[v]]=true;
				odeg[i]++;
				ideg[blkid[v]]++;
			}
		}
	}
}
bool check()
{
	for(int i=1;i<=n;i++)
		if(!vis[i])
			return false;
	for(int i=1;i<=blkc;i++)
		if(ideg[i]==0||odeg[i]==0)
			return false;
	return true;
}

bool vis2[100];
int ans[100];
bool dfs(int x,int num)
{
	if(num>blkc&&x==1)return true;
	if(num>blkc||(x==1&&num!=1))return false;
	vis2[x]=true;
	ans[num]=x;
	for(int i=1;i<=blkc;i++)
		if(nadj[x][i]&&(!vis2[i]||i==1))
			if(dfs(i,num+1))
				return true;
	vis2[x]=false;
	return false;
}

int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(int i=1;i<=n;i++)
			adj[i][0]=0;
		for(int i=1,a,b;i<=m;i++)
		{
			scanf("%d%d",&a,&b);
			adj[a][++adj[a][0]]=b;
		}
		blkc=0;
		memset(vis,0,sizeof vis);
		bool fail=false;
		if(mark_blk(1))
			make_new_graph();
		else
			fail=true;
		memset(vis2,0,sizeof vis2);
		if(!fail&&check()&&dfs(1,1))
		{
			for(int i=1;i<=blkc;i++)
				for(int j=0;j<(int)cont[ans[i]].size();j++)
					printf("%d ",cont[ans[i]][j]);
			puts("1");
		}
		else
			puts("There is no route, Karl!");
	}
	return 0;
}
