#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
#define MAXN 40005
int N,M,Q,P[MAXN][20],L[MAXN],fa[MAXN],dis[MAXN];
struct node{int y,v;node(){};node(int a,int b):y(a),v(b){}};
vector<node>E[MAXN];
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
		node t=E[u][i];
		if(t.y==v)continue;
		dis[t.y]=dis[u]+t.v;
		dfs(t.y,u);
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
	scanf("%d%d",&N,&M);
	for(int i=1,x,y,v;i<=M;i++)
	{
		char s[2];
		scanf("%d%d%d%s",&x,&y,&v,s);
		E[x].push_back(node(y,v));
		E[y].push_back(node(x,v));
	}
	dfs(1,0);
	memset(P,-1,sizeof P);
	for(int i=1;i<=N;i++)
		P[i][0]=fa[i];
	for(int j=1;(1<<j)<N;j++)
		for(int i=1;i<=N;i++)
			if(P[i][j-1]!=-1)
				P[i][j]=P[P[i][j-1]][j-1];
	scanf("%d",&Q);
	for(int q=1,x,y;q<=Q;q++)
	{
		scanf("%d%d",&x,&y);
		int ans=LCA(x,y);
		printf("%d\n",dis[x]+dis[y]-2*dis[ans]);
	}
	return 0;
}
