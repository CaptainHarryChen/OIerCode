#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=16005;

struct Edge
{
	int v;
	Edge *nxt;
};
Edge E[MAXN*2],*V[MAXN],*cur=E;
void add_edge(int u,int v)
{
	cur->v=v;
	cur->nxt=V[u];
	V[u]=cur++;
	cur->v=u;
	cur->nxt=V[v];
	V[v]=cur++;
}

int cnt[MAXN],val[MAXN];
int ans,cent[MAXN],tot;
void solve(int n,int u,int pa=0)
{
	cnt[u]=1;
	for(Edge *p=V[u];p;p=p->nxt)
		if(p->v!=pa)
		{
			solve(n,p->v,u);
			cnt[u]+=cnt[p->v];
			val[u]=max(val[u],cnt[p->v]);
		}
	val[u]=max(val[u],n-cnt[u]);
	if(ans>val[u])
	{
		ans=val[u];
		tot=1;
		cent[1]=u;
	}
	else if(ans==val[u])
		cent[++tot]=u;
}

int main()
{
	int n,a,b;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add_edge(a,b);
	}
	ans=0x7FFFFFFF;
	solve(n,1);
	printf("%d %d\n",ans,tot);
	sort(cent+1,cent+tot+1);
	for(int i=1;i<tot;i++)
		printf("%d ",cent[i]);
	printf("%d\n",cent[tot]);
	return 0;
}
