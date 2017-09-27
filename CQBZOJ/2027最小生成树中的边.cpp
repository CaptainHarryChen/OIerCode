#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXM=100005;
struct Edge
{
	int u,v,val,id;
	Edge(){}
	Edge(int a,int b,int c,int d):u(a),v(b),val(c),id(d){}
	bool operator < (const Edge &t)const
	{
		return val<t.val||(val==t.val&&id<t.id);
	}
};
int S[MAXN];
int root(int x)
{
	if(S[x]==x)
		return x;
	return S[x]=root(S[x]);
}
Edge E[MAXM];
int ans[MAXM];
int vis[MAXM];
vector<Edge>V[MAXN];
int dfn[MAXN],low[MAXN],dfc,last;
void tarjan(int u,int val)
{
	dfn[u]=low[u]=++dfc;
	for(int i=0;i<(int)V[u].size();i++)
		if(vis[V[u][i].id]!=val&&V[u][i].val==val)
		{
			vis[V[u][i].id]=val;
			if(dfn[V[u][i].v]<=last)
			{
				tarjan(V[u][i].v,val);
				low[u]=min(low[u],low[V[u][i].v]);
				if(V[u][i].val==val)
				{
					if(low[V[u][i].v]>dfn[u])
						ans[V[u][i].id]=1;
					else
						ans[V[u][i].id]=2;
				}
			}
			else
			{
				low[u]=min(low[u],dfn[V[u][i].v]);
				ans[V[u][i].id]=2;
			}
		}
}
int main()
{
	int N,M,r1,r2;
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].val);
		E[i].id=i;
	}
	sort(E+1,E+M+1);
	for(int i=1;i<=N;i++)
		S[i]=i;
	for(int i=1,k;i<=M;)
	{
		k=i;
		do
		{
			r1=root(E[i].u);
			r2=root(E[i].v);
			if(r1==r2)
				ans[E[i].id]=3;
			i++;
		}while(E[i].val==E[i-1].val);
		for(int j=k;j<i;j++)
		{
			if(ans[E[j].id]==3)
				continue;
			r1=root(E[j].u);
			r2=root(E[j].v);
			V[r1].push_back(Edge(r1,r2,E[j].val,E[j].id));
			V[r2].push_back(Edge(r2,r1,E[j].val,E[j].id));
		}
		last=dfc;
		for(int j=k;j<i;j++)
		{
			if(ans[E[j].id]==3)
				continue;
			r1=root(E[j].u);
			r2=root(E[j].v);
			if(r1!=r2)
				S[r1]=r2;
			if(dfn[r1]<=last)
				tarjan(r1,E[k].val);
		}
	}
	for(int i=1;i<=M;i++)
		if(ans[i]==1)
			puts("any");
		else if(ans[i]==2)
			puts("at least one");
		else
			puts("none");
	return 0;
}
