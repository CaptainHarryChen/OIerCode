#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
#define MAXN 110
#define MAXE MAXN*MAXN
int n,m,ans;
struct Edge
{
	int id,val;
	Edge *nxt;
	Edge(){nxt=NULL;}
	Edge(int i,int v){id=i;val=v;nxt=NULL;}
}E[MAXE],*V[MAXN],*cur;
void add_edge(int x,int y,int val)
{
	*cur=Edge(y,val);
	cur->nxt=V[x];
	V[x]=cur++;
	*cur=Edge(x,val);
	cur->nxt=V[y];
	V[y]=cur++;
}
struct cmp
{
	bool operator () (Edge *a,Edge *b)
	{return a->val>b->val;}
};
priority_queue<Edge*,vector<Edge*>,cmp>Q;
bool used[MAXN];
void Prim()
{
	used[1]=1;
	for(Edge *p=V[1];p;p=p->nxt)
		if(!used[p->id])
			Q.push(p);
	while(!Q.empty())
	{
		Edge *t=Q.top();
		Q.pop();
		if(used[t->id])
			continue;
		ans+=t->val;
		used[t->id]=1;
		for(Edge *p=V[t->id];p;p=p->nxt)
			if(!used[p->id])
				Q.push(p);
	}
}
int main()
{
	freopen("Prim_data.in","r",stdin);
	cur=E;
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&x);
			add_edge(i,j,x);
		}
	Prim();
	printf("%d\n",ans);
	return 0;
}
