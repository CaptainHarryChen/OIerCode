#include<cstdio>
#include<cstring>
#include<bitset>
using namespace std;
const int MAXN=2018;

struct TwoSAT
{
	bitset<MAXN> G[MAXN];
	void AddOr(int u,int v)
	{
		bool f1=0,f2=0;
		if(u<0)
			u=-u,f1=1;
		if(v<0)
			v=-v,f2=1;
		u--;v--;
		G[(u*2)^f1][(v*2+1)^f2]=1;
		G[(v*2)^f2][(u*2+1)^f1]=1;
	}
	void Floyd(int n)
	{
		for(int k=0;k<2*n;k++)
			for(int i=0;i<2*n;i++)
				if(G[i][k])
					G[i]|=G[k];
		for(int i=0;i<2*n;i++)
			if(G[i][i^1])
				for(int j=0;j<2*n;j++)
					G[i][j]=1,G[j][i^1]=1;
		for(int k=0;k<2*n;k++)
			for(int i=0;i<2*n;i++)
				if(G[i][k])
					G[i]|=G[k];
	}
	void dfs(int u,int n,int ans[])
	{
		if(ans[u]!=-1)
			return;
		ans[u]=1;ans[u^1]=0;
		for(int i=0;i<2*n;i++)
			if(G[u][i])
				dfs(i,n,ans);
	}
	void solve(int ans[],int u,int v,int n)
	{
		dfs(u,n,ans);dfs(v^1,n,ans);
		for(int i=0;i<n*2;i++)
			if(ans[i]==-1)
				dfs(i,n,ans);
	}
}F,G;

int n,m1,m2;
int ans[MAXN];

int main()
{
	scanf("%d%d%d",&n,&m1,&m2);
	for(int i=1,u,v;i<=m1;i++)
	{
		scanf("%d%d",&u,&v);
		F.AddOr(u,v);
	}
	F.Floyd(n);
	for(int i=1,u,v;i<=m2;i++)
	{
		scanf("%d%d",&u,&v);
		G.AddOr(u,v);
	}
	G.Floyd(n);
	for(int i=0;i<n*2;i++)
		for(int j=0;j<n*2;j++)
			if(i!=j&&(i^1)!=j&&F.G[i][j]!=G.G[i][j])
			{
				memset(ans,-1,sizeof ans);
				if(F.G[i][j])
					G.solve(ans,i,j,n);
				else
					F.solve(ans,i,j,n);
				for(int k=0;k<n;k++)
					printf("%d ",ans[k*2+1]);
				puts("");
				return 0;
			}
	puts("SIMILAR");
	return 0;
}
