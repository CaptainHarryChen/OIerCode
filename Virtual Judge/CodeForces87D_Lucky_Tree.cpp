#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=200005;

struct Edge
{
	int u,v,d,id,dep;
	bool operator < (const Edge &t)const
	{return d<t.d||(d==t.d&&dep>t.dep);}
};

int dsu[MAXN],cnt[MAXN];
int Root(int x)
{
	if(dsu[x]==0)
		return x;
	return dsu[x]=Root(dsu[x]);
}

int N;
vector<int> adj[MAXN],id[MAXN];
Edge E[MAXN];
long long ans[MAXN];
int tmp[MAXN];

void dfs(int u,int fa=0,int deep=1)
{
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i];
		if(v!=fa)
		{
			E[id[u][i]].dep=deep;
			if(E[id[u][i]].u!=u)
				swap(E[id[u][i]].u,E[id[u][i]].v);
			dfs(v,u,deep+1);
		}
	}
}

int main()
{
	scanf("%d",&N);
	for(int i=1;i<N;i++)
	{
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].d);
		E[i].id=i;
		adj[E[i].u].push_back(E[i].v);
		id[E[i].u].push_back(i);
		adj[E[i].v].push_back(E[i].u);
		id[E[i].v].push_back(i);
	}
	dfs(1);
	sort(E+1,E+N);
	for(int i=1;i<=N;i++)
		cnt[i]=1;
	int last=1;
	for(int i=2;i<=N;i++)
		if(E[i].d!=E[i-1].d)
		{
			for(int j=last;j<i;j++)
			{
				int r1=Root(E[j].u),r2=Root(E[j].v);
				tmp[E[j].u]=r1;
				tmp[E[j].v]=r2;
			}
			for(int j=last;j<i;j++)
			{
				dsu[tmp[E[j].v]]=tmp[E[j].u];
				cnt[tmp[E[j].u]]+=cnt[tmp[E[j].v]];
			}
			for(int j=last;j<i;j++)
			{
				int r=Root(E[j].u);
				ans[E[j].id]=2LL*(cnt[r]-cnt[E[j].v])*cnt[E[j].v];
			}
			last=i;
		}
	long long mx=0,num=0;
	for(int i=1;i<N;i++)
		mx=max(mx,ans[i]);
	for(int i=1;i<N;i++)
		num+=(ans[i]==mx);
	printf("%I64d %I64d\n",mx,num);
	for(int i=1;i<N;i++)
		if(ans[i]==mx)
			printf("%d ",i);
	puts("");
	
	return 0;
}
