#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXM=1000005;
struct Edge
{
	int id;
	Edge *next;
}E[MAXM*2],*V[MAXN],*cur=E;
void add_edge(int a,int b)
{
	cur->id=b;
	cur->next=V[a];
	V[a]=cur++;
	cur->id=a;
	cur->next=V[b];
	V[b]=cur++;
}
int bricnt;
pair<int,int> bridges[MAXM];
int dfn[MAXN],dfc,low[MAXN];
int type[MAXN];
int rcntA,rcntB;
int sumA[MAXN],sumB[MAXN];
void dfs(int id,int fa=-1)
{
	sumA[id]=(type[id]&1)==1;
	sumB[id]=(type[id]&2)==2;
	dfn[id]=++dfc;
	low[id]=dfn[id];
	for(Edge *p=V[id];p;p=p->next)
		if(!dfn[p->id])
		{
			dfs(p->id,id);
			sumA[id]+=sumA[p->id];
			sumB[id]+=sumB[p->id];
			low[id]=min(low[p->id],low[id]);
			if(low[p->id]>dfn[id]&&(sumA[p->id]==0||sumB[p->id]==0||sumA[p->id]==rcntA||sumB[p->id]==rcntB))
				bridges[++bricnt]=make_pair(id,p->id);
		}
		else if(p->id!=fa)
			low[id]=min(low[id],dfn[p->id]);
}
int main()
{
	int n,m,a,b,k,l;
	scanf("%d%d%d%d",&n,&m,&k,&l);
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&a);
		rcntA++;
		type[a]+=1;
	}
	for(int i=1;i<=l;i++)
	{
		scanf("%d",&b);
		rcntB++;
		type[b]+=2;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		add_edge(a,b);
	}
	dfs(1);
	printf("%d\n",bricnt);
	for(int i=1;i<=bricnt;i++)
		printf("%d %d\n",bridges[i].first,bridges[i].second);
	return 0;
}
 