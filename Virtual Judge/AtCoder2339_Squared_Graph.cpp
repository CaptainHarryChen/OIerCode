#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int n,m;
vector<int> adj[MAXN];
int col[MAXN];

bool dfs(int u,int color)
{
	if(col[u])
		return color==col[u];
	col[u]=color;
	bool ret=true;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i];
		if(!dfs(v,color==1?2:1))
			ret=false;
	}
	return ret;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int a=0,b=0,c=0;
	for(int i=1;i<=n;i++)
		if(!col[i])
		{
			if(adj[i].size()==0U)
				c++,col[i]=1;
			else
			{
				if(dfs(i,1))
					a++;
				else
					b++;
			}
		}
	long long ans=1LL*c*c+2LL*c*(n-c)+2LL*a*a+2LL*a*b+1LL*b*b;
	printf("%lld\n",ans);

	return 0;
}
