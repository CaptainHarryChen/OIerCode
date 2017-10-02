#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=100,MAXM=10005;
typedef pair<int,int> State;
struct Edge
{
	int v,val;
	Edge *next;
};
struct Graph
{
	Edge E[MAXM*2],*V[MAXN],*cur;
	Graph(){clear();}
	void clear(){cur=E;}
	void add_edge(int a,int b,int c)
	{
		cur->v=b;cur->val=c;
		cur->next=V[a];
		V[a]=cur++;
		cur->v=a;cur->val=c;
		cur->next=V[b];
		V[b]=cur++;
	}
};
Graph G;
int dis[MAXN];
priority_queue<State>Q;
void Dijkstra()
{
	memset(dis,0x3F,sizeof dis);
	dis['Z'-'A']=0;
	Q.push(State(0,'Z'-'A'));
	State t;
	while(!Q.empty())
	{
		t=Q.top();
		Q.pop();
		if(t.first>dis[t.second])
			continue;
		for(Edge *p=G.V[t.second];p;p=p->next)
			if(dis[p->v]>t.first+p->val)
			{
				dis[p->v]=t.first+p->val;
				Q.push(State(dis[p->v],p->v));
			}
	}
}
int main()
{
	int m,val;
	char u[3],v[3];
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%s%s%d",u,v,&val);
		G.add_edge(u[0]-'A',v[0]-'A',val);
	}
	Dijkstra();
	int mint=0x3F3F3F3F,fast;
	for(int i=0;i<25;i++)
		if(dis[i]<mint)
		{
			mint=dis[i];
			fast=i;
		}
	printf("%c %d\n",'A'+fast,mint);
	return 0;
}
