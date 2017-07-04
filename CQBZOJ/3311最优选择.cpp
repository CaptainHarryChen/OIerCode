#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 55
namespace ISAP
{
	const int MAX_NODE=5005,MAX_EDGE=40005,INF=0x7FFFFFFF;
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
					if(dis[S]>=N)return augco-augc;
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
int n,m;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
inline bool legal(int x,int y)
{return x>0&&y>0&&x<=n&&y<=m;}
inline int ID(int x,int y,int f)
{return (((x-1)*m+y)<<1)-1+f;}
int main()
{
	int x,ans=0;
	scanf("%d%d",&n,&m);
	using namespace ISAP;
	Init(0,((n*m)<<1)+1,((n*m)<<1)+2);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&x);
			if((i+j)&1)
				add_edge(S,ID(i,j,0),x);
			else
				add_edge(ID(i,j,0),T,x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&x);
			ans+=(x<<1);
			if((i+j)&1)
			{
				add_edge(S,ID(i,j,1),x);
				add_edge(ID(i,j,0),T,x);
			}
			else
			{
				add_edge(S,ID(i,j,0),x);
				add_edge(ID(i,j,1),T,x);
			}
		}
	int tx,ty;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if((i+j)&1)
				add_edge(ID(i,j,1),ID(i,j,0),INF);
			else
				add_edge(ID(i,j,0),ID(i,j,1),INF);
			for(int k=0;k<4;k++)
			{
				tx=i+dir[k][0];ty=j+dir[k][1];
				if(!legal(tx,ty))continue;
				if((i+j)&1)
					add_edge(ID(i,j,1),ID(tx,ty,0),INF);
				else
					add_edge(ID(tx,ty,0),ID(i,j,1),INF);
			}
		}
	printf("%d\n",ans-iSap());
	return 0;
}
