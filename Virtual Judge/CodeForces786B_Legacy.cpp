#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=100005,MAXM=2000005,DIV=MAXN*4;
const long long LLF=0x3F3F3F3F3F3F3F3FLL;
struct Edge
{
	int v,d;
	Edge *next;
};
struct Graph
{
	Edge E[MAXM*4],*V[MAXN*8],*cur;
	Graph()
	{cur=E;}
	void add_edge(int a,int b,int c)
	{
		cur->v=b;
		cur->d=c;
		cur->next=V[a];
		V[a]=cur++;
	}
};
struct State
{
	int u;
	long long d;
	State(){}
	State(int _u,long long _d)
	{u=_u;d=_d;}
	bool operator > (const State &t)const
	{return d>t.d;}
};
struct SegmentTree
{
	Graph G;
	void Build1(int L,int R,int id=1)
	{
		if(L==R)return;
		Build1(L,(L+R)/2,id*2);
		Build1((L+R)/2+1,R,id*2+1);
		G.add_edge(id*2,id,0);
		G.add_edge(id*2+1,id,0);
	}
	void Build2(int L,int R,int id=1)
	{
		G.add_edge(id+DIV,id,0);
		if(L==R)return;
		Build2(L,(L+R)/2,id*2);
		Build2((L+R)/2+1,R,id*2+1);
		G.add_edge(id+DIV,id*2+DIV,0);
		G.add_edge(id+DIV,id*2+1+DIV,0);
	}
	void get_seg_id(int l,int r,int res[],int &cur,int L,int R,int id=1)
	{
		if(R<l||r<L)
			return;
		if(l<=L&&R<=r)
		{
			res[++cur]=id;
			return;
		}
		get_seg_id(l,r,res,cur,L,(L+R)/2,id*2);
		get_seg_id(l,r,res,cur,(L+R)/2+1,R,id*2+1);
	}
};
priority_queue<State,vector<State>,greater<State> >Q;
long long dis[MAXN*8];
void Dijkstra(Graph &G,int s)
{
	memset(dis,0x3F,sizeof dis);
	dis[s]=0;
	Q.push(State(s,0));
	State t;
	while(!Q.empty())
	{
		t=Q.top();Q.pop();
		if(t.d>dis[t.u])
			continue;
		for(Edge *p=G.V[t.u];p;p=p->next)
			if(dis[p->v]>dis[t.u]+p->d)
			{
				dis[p->v]=dis[t.u]+p->d;
				Q.push(State(p->v,dis[p->v]));
			}
	}
}
SegmentTree ST;
int ids[MAXN],cur;
int main()
{
	int n,q,s;
	scanf("%d%d%d",&n,&q,&s);
	ST.Build1(1,n);
	ST.Build2(1,n);
	int t,u,v,l,r,w,a,b;
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&t);
		if(t==1)
		{
			scanf("%d%d%d",&u,&v,&w);
			cur=0;ST.get_seg_id(u,u,ids,cur,1,n);a=ids[1];
			cur=0;ST.get_seg_id(v,v,ids,cur,1,n);b=ids[1];
			ST.G.add_edge(a,b+DIV,w);
		}
		else if(t==2)
		{
			scanf("%d%d%d%d",&u,&l,&r,&w);
			cur=0;ST.get_seg_id(u,u,ids,cur,1,n);a=ids[1];
			cur=0;ST.get_seg_id(l,r,ids,cur,1,n);
			for(int j=1;j<=cur;j++)
				ST.G.add_edge(a,ids[j]+DIV,w);
		}
		else
		{
			scanf("%d%d%d%d",&v,&l,&r,&w);
			cur=0;ST.get_seg_id(v,v,ids,cur,1,n);b=ids[1];
			cur=0;ST.get_seg_id(l,r,ids,cur,1,n);
			for(int j=1;j<=cur;j++)
				ST.G.add_edge(ids[j],b+DIV,w);
		}
	}
	cur=0;ST.get_seg_id(s,s,ids,cur,1,n);
	Dijkstra(ST.G,ids[1]+DIV);
	long long ans;
	for(int i=1;i<=n;i++)
	{
		cur=0;ST.get_seg_id(i,i,ids,cur,1,n);
		ans=dis[ids[1]];
		if(ans==LLF)
			ans=-1;
		printf("%I64d ",ans);
	}
	puts("");
	return 0;
}
