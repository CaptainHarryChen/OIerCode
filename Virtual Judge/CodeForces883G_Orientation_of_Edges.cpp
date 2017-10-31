#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=300005;
struct Edge
{
	int v,t,id;
	Edge *next;
};
Edge E[MAXN*2],*V[MAXN],*cur=E;
void add_edge(int u,int v,int t,int i)
{
	cur->v=v;cur->t=t;cur->id=i;
	cur->next=V[u];
	V[u]=cur++;
	if(t==2)
	{
		cur->v=u;cur->t=t;cur->id=i;
		cur->next=V[v];
		V[v]=cur++;
	}
}
int ans1,ans2;
int dir1[MAXN],dir2[MAXN];
bool vis1[MAXN],vis2[MAXN];
int e[MAXN][3];
void dfs1(int u)
{
	vis1[u]=true;
	ans1++;
	for(Edge *p=V[u];p;p=p->next)
		if(!vis1[p->v])
		{
			if(p->t==2)
				dir1[p->id]=(p->v==e[p->id][1]);
			dfs1(p->v);
		}
}
void dfs2(int u)
{
	vis2[u]=true;
	ans2++;
	for(Edge *p=V[u];p;p=p->next)
		if(!vis2[p->v])
		{
			if(p->t==2)
			{
				if(dir2[p->id]==-1)
				{
					dir2[p->id]=!(p->v==e[p->id][1]);
					continue;
				}
			}
			dfs2(p->v);
		}
}
int main()
{
	int n,m,s,a,b,t;
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&t,&a,&b);
		add_edge(a,b,t,i);
		e[i][0]=a;e[i][1]=b;e[i][2]=t;
	}
	dfs1(s);
	memset(dir2,-1,sizeof dir2);
	dfs2(s);
	printf("%d\n",ans1);
	for(int i=1;i<=m;i++)
		if(e[i][2]==2)
			printf("%c",dir1[i]?'+':'-');
	puts("");
	printf("%d\n",ans2);
	for(int i=1;i<=m;i++)
		if(e[i][2]==2)
			printf("%c",dir2[i]?'+':'-');
	puts("");
	return 0;
}
