#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=1005,MAXM=200005;
 
int N,M;
vector<int> adj[MAXN];
int E[MAXM][2];
 
int p[MAXN][MAXN],q[MAXN][MAXN];
bool vis[MAXN];
 
void mark(int s,int u,int id,int mk[])
{
	if(u==s||vis[u])return;
	vis[u]=true;
	mk[u]=id;
	for(int i=0;i<(int)adj[u].size();i++)
		mark(s,adj[u][i],id,mk);
}
 
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=1,a,b;i<=M;i++)
	{
		scanf("%d%d",&a,&b);
		E[i][0]=a;E[i][1]=b;
		adj[a].push_back(b);
	}
	
	for(int i=1;i<=N;i++)
	{
		memset(vis,0,sizeof vis);
		int id=0;
		for(int j=0;j<(int)adj[i].size();j++)
			mark(i,adj[i][j],++id,p[i]);
		memset(vis,0,sizeof vis);
		reverse(adj[i].begin(),adj[i].end());
		id=adj[i].size();
		for(int j=0;j<(int)adj[i].size();j++)
			mark(i,adj[i][j],id--,q[i]);
	}
	
	for(int i=1;i<=M;i++)
		if((p[E[i][1]][E[i][0]]>0)==(p[E[i][0]][E[i][1]]!=q[E[i][0]][E[i][1]]))
			puts("same");
		else
			puts("diff");
	
	return 0;
}
