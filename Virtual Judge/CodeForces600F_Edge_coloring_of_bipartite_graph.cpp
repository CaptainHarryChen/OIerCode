#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=2005,MAXM=100005;

int A,B,M;
vector<int> adj[MAXN];
int deg[MAXN];
int link[MAXN][MAXN];
int eid[MAXN][MAXN];
int ans[MAXM];

int main()
{
	int num=0;
	scanf("%d%d%d",&A,&B,&M);
	for(int i=1;i<=M;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		v+=A;
		eid[u][v]=i;
		eid[v][u]=i;
		adj[u].push_back(v);
		adj[v].push_back(u);
		deg[u]++;deg[v]++;
		num=max(num,deg[u]);
		num=max(num,deg[v]);
		
		int cu=1,cv=1;
		while(link[u][cu])
			cu++;
		while(link[v][cv])
			cv++;
		if(cu==cv)
		{
			link[u][cu]=v;
			link[v][cv]=u;
		}
		else
		{
			int x=u,y=v,z,w;
			link[u][cu]=v;
			for(;;)
			{
				z=link[y][cu];
				link[y][cu]=x;
				link[y][cv]=z;
				if(z==0)
					break;
				w=link[z][cv];
				link[z][cv]=y;
				link[z][cu]=w;
				if(w==0)
					break;
				x=z,y=w;
			}
		}
	}
	for(int i=1;i<=A+B;i++)
		for(int c=1;c<=num;c++)
			if(link[i][c])
				ans[eid[i][link[i][c]]]=c;
	printf("%d\n",num);
	for(int i=1;i<=M;i++)
		printf("%d ",ans[i]);
	puts("");
	
	return 0;
}
