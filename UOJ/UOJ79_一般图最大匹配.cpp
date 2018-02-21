#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=505,MAXM=125000;

int n,m;
int match[MAXN],mk[MAXN],nxt[MAXN],vis[MAXN];
vector<int> adj[MAXN];
queue<int> que;

int fa[MAXN];
int root(int x)
{return fa[x]==x?x:(fa[x]=root(fa[x]));}
void Union(int x,int y)
{
	int r1=root(x),r2=root(y);
	if(r1!=r2)
		fa[r1]=r2;
}

int LCA(int x,int y)
{
	static int ti=0;
	ti++;
	for(;;)
	{
		if(x)
		{
			x=root(x);
			if(vis[x]==ti)
				return x;
			vis[x]=ti;
			if(match[x])
				x=nxt[match[x]];
			else 
				x=0;
		}
		swap(x,y);
	}
}
void group(int u,int pa)
{
	int v,w;
	while(u!=pa)
	{
		v=match[u];
		w=nxt[v];
		if(root(w)!=pa)
			nxt[w]=v;
		if(mk[v]==2)
		{
			mk[v]=1;
			que.push(v);
		}
		Union(u,v);
		Union(v,w);
		u=w;
	}
}

void aug(int S)
{
	for(int i=1;i<=n;i++)
		mk[i]=nxt[i]=0,fa[i]=i;
	while(!que.empty())
		que.pop();
	mk[S]=1;
	que.push(S);
	while(!que.empty())
	{
		int u=que.front();
		que.pop();
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i];
			if(match[u]==v||root(u)==root(v)||mk[v]==2)
				continue;
			else if(mk[v]==1)
			{
				int lca=LCA(u,v);
				if(root(u)!=lca)
					nxt[u]=v;
				if(root(v)!=lca)
					nxt[v]=u;
				group(u,lca);
				group(v,lca);
			}
			else if(match[v]==0)
			{
				nxt[v]=u;
				int x=v,y=u,t;
				while(x)
				{
					t=match[y];
					match[x]=y;
					match[y]=x;
					x=t;
					y=nxt[x];
				}
				return;
			}
			else
			{
				nxt[v]=u;
				mk[v]=2;
				mk[match[v]]=1;
				que.push(match[v]);
			}
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	for(int i=1;i<=n;i++)
		if(match[i]==0)
			aug(i);
	
	int cnt=0;
	for(int i=1;i<=n;i++)
		if(match[i])
			cnt++;
	cnt/=2;
	printf("%d\n",cnt);
	for(int i=1;i<n;i++)
		printf("%d ",match[i]);
	printf("%d\n",match[n]);
	
	return 0;
}
