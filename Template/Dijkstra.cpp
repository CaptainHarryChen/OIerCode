#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
#define MAXN 505
#define MAXE 2005
int n,m,s,t,dis[MAXN],path[MAXN],print[MAXN],p;
struct Edge
{
	int x,v;
	Edge *next;
	Edge():next(NULL){}
	Edge(int a,int b):x(a),v(b),next(NULL){}
}edge[MAXN];
typedef pair<int,int> Po;
priority_queue<Po,vector<Po>,greater<Po> > Q;
void Dijkstra()
{
	memset(dis,0x3F,sizeof dis);
	dis[s]=0;
	Q.push(make_pair(0,s));
	while(!Q.empty())
	{
		Po t=Q.top();Q.pop();
		if(dis[t.second]<t.first)
			continue;
		for(Edge *p=edge[t.second].next;p;p=p->next)
			if(dis[p->x]>dis[t.second]+p->v)
			{
				dis[p->x]=dis[t.second]+p->v;
				path[p->x]=t.second;
				Q.push(make_pair(dis[p->x],p->x));
			}
	}
}
int main()
{
	freopen("Dijkstra_data.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int q=1,i,j,w;q<=m;q++)
	{
		scanf("%d%d%d",&i,&j,&w);
		Edge *p=new Edge(j,w);
		p->next=edge[i].next;
		edge[i].next=p;
	}
	scanf("%d%d",&s,&t);
	Dijkstra();
	printf("%d\n",dis[t]);
	int x=path[t];
	while(x!=s)
	{
		print[p++]=x;
		x=path[x];
	}
	printf("%d ",s);
	for(int i=p-1;i>=0;i--)
		printf("%d ",print[i]);
	printf("%d\n",t);
	return 0;
}
