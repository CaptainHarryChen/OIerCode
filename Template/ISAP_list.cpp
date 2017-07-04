#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 205
namespace ISAP
{
	const int MAX_NODE=205,MAX_EDGE=205<<1,INF=0x7FFFFFFF;
	struct Edge
	{
		int x,w;
		Edge *next,*back;
		Edge(){}
		Edge(int x,int w):x(x),w(w){}
	}_new[MAX_EDGE],*head[MAX_NODE];
	int top,S,T,N;
	int dis[MAX_NODE],cnt_d[MAX_NODE];
	void add_edge(int x,int y,int w)
	{
		_new[top]=Edge(y,w);
		_new[top].next=head[x];
		_new[top].back=_new+top+1;
		head[x]=_new+top;
		top++;
		_new[top]=Edge(x,0);
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
	int aug(int now,int augco)
	{
		if(now==T)return augco;
		int augc=augco,mn=N,delta;
		Edge *p;
		for(p=head[now];p;p=p->next)
			if(p->w>0)
			{
				if(dis[p->x]==dis[now]-1)
				{
					delta=min(p->w,augc);
					delta=aug(p->x,delta);
					p->w-=delta;
					p->back->w+=delta;
					augc-=delta;
					if(dis[S]>N)return augco-augc;
					if(!augc)break;
				}
				mn=min(mn,dis[p->x]);
			}
		if(augc==augco)
		{
			cnt_d[dis[now]]--;
			if(!cnt_d[dis[now]])
				dis[S]=N;
			dis[now]=mn+1;
			cnt_d[dis[now]]++;
		}
		return augco-augc;
	}
	int iSap()
	{
		memset(dis,0,sizeof dis);
		memset(cnt_d,0,sizeof cnt_d);
		cnt_d[0]=N;
		int flow=0;
		while(dis[S]<N)
			flow+=aug(S,INF);
		return flow;
	}
}
int main()
{
	freopen("ISAP_list_data.in","r",stdin);
	int n,m,x,y,w;
	scanf("%d%d",&n,&m);
	ISAP::Init(1,m,m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&x,&y,&w);
		ISAP::add_edge(x,y,w);
	}
	printf("%d\n",ISAP::iSap());
	return 0;
}
