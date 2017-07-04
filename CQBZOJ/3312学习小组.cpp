#include<cstdio>
#include<cstring>
#include<queue>
#define MAXN 105
using namespace std;
namespace ValueFlow
{
	const int MAX_NODE=205,MAX_EDGE=41000,INF=0x7FFFFFFF;
	struct Edge
	{
		int x,w,v;
		Edge *next,*back;
		Edge(){}
		Edge(int x,int w,int v):x(x),w(w),v(v){}
	}_new[MAX_EDGE],*head[MAX_NODE],*path2[MAX_NODE];
	int top,S,T,N;
	int path1[MAX_NODE],dis[MAX_NODE];
	bool vis[MAX_NODE];
	void add_edge(int x,int y,int w,int v)
	{
		_new[top]=Edge(y,w,v);
		_new[top].next=head[x];
		_new[top].back=_new+top+1;
		head[x]=_new+top;
		top++;
		_new[top]=Edge(x,0,-v);
		_new[top].next=head[y];
		_new[top].back=_new+top-1;
		head[y]=_new+top;
		top++;
	}
	void Init(int s,int t,int n)
	{
		top=0;
		memset(head,0,sizeof head);
		S=s;T=t;N=n;
	}
	int SPFA()
	{
		memset(vis,0,sizeof vis);
		memset(dis,0x3F,sizeof dis);
		queue<int>Q;
		Q.push(S);
		vis[S]=1;
		dis[S]=0;
		while(!Q.empty())
		{
			int t=Q.front();
			Q.pop();vis[t]=0;
			for(Edge *p=head[t];p;p=p->next)
				if(p->w>0&&dis[p->x]>dis[t]+p->v)
				{
					dis[p->x]=dis[t]+p->v;
					path1[p->x]=t;
					path2[p->x]=p;
					if(!vis[p->x])
					{
						Q.push(p->x);
						vis[p->x]=1;
					}
				}
		}	
		if(dis[T]==0x3F3F3F3F)
			return 0;
		int x=T,mn=0x7FFFFFFF;
		while(x!=S)
		{
			mn=min(mn,path2[x]->w);
			x=path1[x];
		}
		x=T;
		while(x!=S)
		{	
			path2[x]->w-=mn;
			path2[x]->back->w+=mn;
			x=path1[x];
		}
		return mn;
	}
	void getValueFlow(int &flow,int &ans)
	{
		int t;
		flow=0;
		ans=0;
		while(t=SPFA(),t)
			flow+=t,ans+=dis[T]*t;
	}
}
int C[MAXN],F[MAXN];
int main()
{
	int n,m,k,x;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
		scanf("%d",&C[i]);
	for(int j=1;j<=m;j++)
		scanf("%d",&F[j]);
	using namespace ValueFlow;
	Init(0,n+m+1,n+m+2);
	for(int i=1;i<=n;i++)
	{
		add_edge(S,i,k,0);
		add_edge(i,T,k-1,0);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%1d",&x);
			if(x)
				add_edge(i,j+n,1,0);
		}
	for(int j=1;j<=m;j++)
		for(int i=1;i<=n;i++)
			add_edge(j+n,T,1,C[j]*(2*i-1)-F[j]);
	int ans,flow;
	getValueFlow(flow,ans);
	printf("%d\n",ans);
	return 0;
}
