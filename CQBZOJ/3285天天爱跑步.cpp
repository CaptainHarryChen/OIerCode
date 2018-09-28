#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
const int MAXN=300005,MAXLOG=20;

int N,M;

struct Edge
{
	int v;
	Edge *nxt;
}E[MAXN*2],*adj[MAXN],*ecnt=E;

void AddEdge(int u,int v)
{
	ecnt->v=v;
	ecnt->nxt=adj[u];
	adj[u]=ecnt++;
}

int W[MAXN];
int S[MAXN],T[MAXN],lca[MAXN],len[MAXN];

int fa[MAXN][MAXLOG],dep[MAXN];

void dfs(int u)
{
	for(Edge *p=adj[u];p;p=p->nxt)
		if(p->v!=fa[u][0])
		{
			fa[p->v][0]=u;
			dep[p->v]=dep[u]+1;
			dfs(p->v);
		}
}
void InitLCA()
{
	dep[1]=1;
	dfs(1);
	for(int j=1;j<MAXLOG;j++)
		for(int i=1;i<=N;i++)
			if(dep[i]-(1<<j)>0)
				fa[i][j]=fa[fa[i][j-1]][j-1];
}
int LCA(int u,int v)
{
	if(dep[u]>dep[v])
		swap(u,v);
	for(int j=MAXLOG-1;j>=0;j--)
		if(dep[v]-(1<<j)>=dep[u])
			v=fa[v][j];
	if(u==v)
		return u;
	for(int j=MAXLOG-1;j>=0;j--)
		if(dep[u]-(1<<j)>0&&fa[u][j]!=fa[v][j])
			u=fa[u][j],v=fa[v][j];
	return fa[u][0];
}

int ans[MAXN];
vector<int> P[MAXN],ed[MAXN];
int st[MAXN];
int cntS[MAXN*4],cntT[MAXN*4];
int mxdep;

void solve1(int u)
{
    int tmp=0;
    if(mxdep-dep[u]-W[u]>=0)
        tmp=cntS[mxdep-dep[u]-W[u]];
    for(Edge *p=adj[u];p;p=p->nxt)
    {
        int v=p->v;
        if(v!=fa[u][0])
            solve1(v);
    }
    cntS[mxdep-dep[u]]+=st[u];
    for(int i=0;i<(int)P[u].size();i++)
        cntS[mxdep-dep[S[P[u][i]]]]--;
    if(mxdep-dep[u]-W[u]>=0)
        ans[u]+=cntS[mxdep-dep[u]-W[u]]-tmp;
}
void solve2(int u)
{
    int tmp=0;
    tmp=cntT[W[u]-dep[u]+mxdep];
    for(Edge *p=adj[u];p;p=p->nxt)
    {
        int v=p->v;
        if(v!=fa[u][0])
            solve2(v);
    }
    for(int i=0;i<(int)ed[u].size();i++)
        if(len[ed[u][i]]-dep[u]+mxdep<=mxdep*2)
            cntT[len[ed[u][i]]-dep[u]+mxdep]++;
    for(int i=0;i<(int)P[u].size();i++)
        cntT[len[P[u][i]]-dep[T[P[u][i]]]+mxdep]--;
    ans[u]+=cntT[W[u]-dep[u]+mxdep]-tmp;
}

int main()
{
	scanf("%d%d",&N,&M);
	for(int i=1;i<N;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		AddEdge(u,v);
		AddEdge(v,u);
	}
	for(int i=1;i<=N;i++)
		scanf("%d",&W[i]);

    InitLCA();
	for(int i=1;i<=M;i++)
    {
		scanf("%d%d",&S[i],&T[i]);
		st[S[i]]++;
		ed[T[i]].push_back(i);
		lca[i]=LCA(S[i],T[i]);
		P[lca[i]].push_back(i);
		len[i]=dep[S[i]]+dep[T[i]]-2*dep[lca[i]];
		if(W[lca[i]]==dep[S[i]]-dep[lca[i]])
            ans[lca[i]]++;
    }

	for(int i=1;i<=N;i++)
        mxdep=max(mxdep,dep[i]);
	solve1(1);
	solve2(1);

	for(int i=1;i<=N;i++)
        printf("%d%c",ans[i]," \n"[i==N]);
	return 0;
}
