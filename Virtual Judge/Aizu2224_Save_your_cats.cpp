#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
using namespace std;
#define MAXN 10005
#define MAXM 1000005
int n,m;
struct Edge
{
	int id;
	double val;
	Edge *nxt;
	Edge(){nxt=NULL;}
	Edge(int i,double v){id=i;val=v;nxt=NULL;}
}E[MAXM],*V[MAXN],*cur;
void add_edge(int x,int y,double val)
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
	{return a->val<b->val;}
};
bool used[MAXN];
double Prim(int s)
{
	double ans=0;
	priority_queue<Edge*,vector<Edge*>,cmp>Q;
	used[s]=1;
	for(Edge *p=V[s];p;p=p->nxt)
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
	return ans;
}
pair<int,int>pile[MAXN];
double dis(int a,int b)
{
	return sqrt((pile[a].first-pile[b].first)*(pile[a].first-pile[b].first)+
	(pile[a].second-pile[b].second)*(pile[a].second-pile[b].second));
}
int main()
{
	int N,M;
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
		scanf("%d%d",&pile[i].first,&pile[i].second);
	cur=E;
	double sum=0;
	for(int j=1,p,q;j<=M;j++)
	{
		scanf("%d%d",&p,&q);
		double tmp=dis(p,q);
		add_edge(p,q,tmp);
		sum+=tmp;
	}
	for(int i=1;i<=N;i++)
		if(!used[i])
			sum-=Prim(i);
	printf("%.3lf\n",sum);
	return 0;
}
