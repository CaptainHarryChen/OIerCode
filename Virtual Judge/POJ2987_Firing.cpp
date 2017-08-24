#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=6005,MAXE=160005;
struct Edge
{
	long long cap;
	int id;
	Edge *next,*back;
	Edge(){}
	Edge(int i,long long c)
	{
		cap=c;
		id=i;
	}
};
Edge *V[MAXN],E[MAXE];
void add_edge(int u,int v,long long c)
{
	static Edge *cur=E;
	*cur=Edge(v,c);
	cur->back=cur+1;
	cur->next=V[u];
	V[u]=cur;
	cur++;
	*cur=Edge(u,0);
	cur->next=V[v];
	cur->back=cur-1;
	V[v]=cur;
	cur++;
}
int d[MAXN],cntd[MAXN];
long long aug(int id,int S,int T,int n,long long augco)
{
	if(id==T)
		return augco;
	long long augc=augco,temp;
	int mind=n;
	for(Edge *p=V[id];p;p=p->next)
		if(p->cap>0LL)
		{
			if(d[id]==d[p->id]+1)
			{
				temp=min(p->cap,augc);
				temp=aug(p->id,S,T,n,temp);
				p->cap-=temp;p->back->cap+=temp;
				augc-=temp;
				if(d[S]>=n)
					return augco-augc;
				if(augc<=0LL)
					break;
			}
			mind=min(mind,d[p->id]);
		}
	if(augco==augc)
	{
		cntd[d[id]]--;
		if(cntd[d[id]]<=0)
			d[S]=n;
		d[id]=mind+1;
		cntd[d[id]]++;
	}
	return augco-augc;
}
long long iSap(int S,int T,int n)
{
	memset(d,0,sizeof d);
	memset(cntd,0,sizeof cntd);
	cntd[0]=n;
	long long flow=0LL;
	while(d[S]<n)
		flow+=aug(S,S,T,n,0x7FFFFFFFFFFFFFFFLL);
	return flow;
}
int ans1;
long long ans2;
bool vis[MAXN];
void Count(int id)
{
	ans1++;
	vis[id]=1;
	for(Edge *p=V[id];p;p=p->next)
		if(p->cap>0&&!vis[p->id])
			Count(p->id);
}
int main()
{
	int n,m,S,T;
	scanf("%d%d",&n,&m);
	S=0,T=n+1;
	long long W=0LL;
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		if(x>0)
		{
			W+=x;
			add_edge(S,i,x);
		}
		if(x<0)
			add_edge(i,T,-x);
	}
	for(int i=1,x,y;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		add_edge(x,y,0x7FFFFFFFFFFFFFFFLL);
	}
	ans2=W-iSap(S,T,n+2);
	Count(S);
	printf("%d %lld\n",ans1-1,ans2);
	return 0;
}
