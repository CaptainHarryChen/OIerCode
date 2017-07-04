#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
#define MAXN 100005
int N,Q,P[MAXN][20],L[MAXN],fa[MAXN];
vector<int>E[MAXN];
int Log(int x)
{
	int j;
	for(j=0;(1<<j)<=x;j++);
	return j-1;
}
void dfs(int u,int v)
{
	fa[u]=v;
	L[u]=L[v]+1;
	for(int i=0;i<(int)E[u].size();i++)
	{
		int t=E[u][i];
		if(t==v)continue;
		dfs(t,u);
	}
}
int LCA(int x,int y)
{
	if(L[x]<L[y])
		swap(x,y);
	if(L[x]>L[y])
		for(int j=Log(L[x]);j>=0;j--)
			if(L[x]-(1<<j)>=L[y])
				x=P[x][j];
	if(x==y)return x;
	for(int j=Log(L[x]);j>=0;j--)
		if(P[x][j]!=-1&&P[x][j]!=P[y][j])
			x=P[x][j],y=P[y][j];
	return fa[x];
}
int main()
{
	scanf("%d%d",&N,&Q);
	for(int i=1,x,y;i<N;i++)
	{
		scanf("%d%d",&x,&y);
		E[x].push_back(y);
		E[y].push_back(x);
	}
	dfs(1,0);
	memset(P,-1,sizeof P);
	for(int i=1;i<=N;i++)
		P[i][0]=fa[i];
	for(int j=1;(1<<j)<N;j++)
		for(int i=1;i<=N;i++)
			if(P[i][j-1]!=-1)
				P[i][j]=P[P[i][j-1]][j-1];
	for(int q=1,x,y;q<=Q;q++)
	{
		scanf("%d%d",&x,&y);
		int ans=LCA(x,y);
		printf("%d\n",ans);
	}
	return 0;
}
