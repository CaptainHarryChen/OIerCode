#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=100005;

vector<int> adj[MAXN];
int deg[MAXN];

int dfs(int u,int fa=-1)
{
	int res=0,temp;
	bool flag=false;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i];
		if(v==fa)
			continue;
		temp=dfs(v,u);
		if(temp==0&&flag==true)
			temp++;
		if(temp==0&&flag==false)
			flag=true;
		res+=temp;
	}
	return res;
}

int main()
{
	int N;
	scanf("%d",&N);
	for(int i=0,u,v;i<N-1;i++)
	{
		scanf("%d%d",&u,&v);
		deg[u]++;
		deg[v]++;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int root=-1;
	for(int i=0;i<N;i++)
		if(deg[i]>=3)
		{
			root=i;
			break;
		}
	if(root==-1)
		puts("1");
	else
		printf("%d\n",dfs(root));
	return 0;
}
