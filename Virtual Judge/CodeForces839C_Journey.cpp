#include<cstdio>
const int MAXN=100005;
struct Edge
{
	int v;
	Edge *next;
};
struct Tree
{
	Edge E[MAXN*2],*V[MAXN],*cur;
	Tree(){cur=E;}
	void add_edge(int a,int b)
	{
		cur->v=b;
		cur->next=V[a];
		V[a]=cur++;
		cur->v=a;
		cur->next=V[b];
		V[b]=cur++;
	}
};
double dp[MAXN];
Tree T;
void dfs(int id,int fa,int dis)
{
	int cnt=0;
	for(Edge *p=T.V[id];p;p=p->next)
		if(p->v!=fa)
			cnt++;
	for(Edge *p=T.V[id];p;p=p->next)
		if(p->v!=fa)
		{
			dfs(p->v,id,dis+1);
			dp[id]+=1.0/cnt*dp[p->v];
		}
	if(cnt==0)
		dp[id]=dis;
}
int main()
{
	int n,a,b;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		T.add_edge(a,b);
	}
	dfs(1,0,0);
	printf("%.15lf\n",dp[1]);
	return 0;
}
