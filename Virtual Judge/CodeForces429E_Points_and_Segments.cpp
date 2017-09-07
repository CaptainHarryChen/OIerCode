#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=400005;
int id[MAXN*2],edge[MAXN][2];
struct Edge
{
	int u,v,segid;
	bool vis;
	Edge *next,*back;
}*V[MAXN*2],E[MAXN*2],*cur=E;
void add_edge(int a,int b,int i)
{
	cur->u=a;
	cur->v=b;
	cur->segid=i;
	cur->next=V[a];
	cur->back=cur+1;
	V[a]=cur++;
	cur->u=b;
	cur->v=a;
	cur->segid=i;
	cur->next=V[b];
	cur->back=cur-1;
	V[b]=cur++;
}
Edge *path[MAXN*2];
int pcnt;
void euler(int id)
{
	for(Edge *p=V[id];p;p=p->next)
		if(!p->vis)
		{
			p->vis=1;
			p->back->vis=1;
			euler(p->v);
			path[++pcnt]=p;
		}
}
bool vis[MAXN*2];
int deg[MAXN*2];
int obb[MAXN*2],ocnt;
bool ans[MAXN];
int main()
{
	int n,m,l,r;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",edge[i],edge[i]+1);
		edge[i][1]++;
		id[i*2-1]=edge[i][0];
		id[i*2]=edge[i][1];
	}
	sort(id+1,id+n*2+1);
	m=unique(id+1,id+n*2+1)-id-1;
	for(int i=1;i<=n;i++)
	{
		l=lower_bound(id+1,id+m+1,edge[i][0])-id;
		r=lower_bound(id+1,id+m+1,edge[i][1])-id;
		add_edge(l,r,i);
		deg[l]++;
		deg[r]++;
	}
	for(int i=1;i<=m;i++)
		if(deg[i]&1)
			obb[++ocnt]=i;
	for(int i=1;i<=ocnt;i+=2)
		add_edge(obb[i],obb[i+1],0);
	for(int i=1;i<=m;i++)
		if(!vis[i])
		{
			pcnt=0;
			euler(i);
			vis[path[pcnt]->u]=1;
			for(int j=pcnt;j>0;j--)
			{
				vis[path[j]->v]=1;
				ans[path[j]->segid]=(path[j]->u<path[j]->v);
			}
		}
	for(int i=1;i<n;i++)
		printf("%d ",(int)ans[i]);
	printf("%d\n",(int)ans[n]);
	return 0;
}
