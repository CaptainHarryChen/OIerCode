#include<cstdio>
#include<cstring>
#include<queue>
#define MAXN 23
using namespace std;
const int INF=0x7FFFFFFF;
namespace ValueFlow
{
	const int MAX_NODE=1005,MAX_EDGE=MAX_NODE*30;
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
char st[MAXN][MAXN],ed[MAXN][MAXN],ct[MAXN][MAXN];
const int dir[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
int main()
{
	int n,m,cnt1=0,cnt2=0,S,T;
	scanf("%d%d",&n,&m);
	S=n*m*2+1,T=n*m*2+2;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",st[i]+1);
		for(int j=1;j<=m;j++)
		{
			st[i][j]-='0';
			cnt1+=st[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ed[i]+1);
		for(int j=1;j<=m;j++)
		{
			ed[i][j]-='0';
			cnt2+=ed[i][j];
		}
	}
	if(cnt1!=cnt2){printf("-1\n");return 0;}
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ct[i]+1);
		for(int j=1;j<=m;j++)
		{
			ct[i][j]-='0';
		}
	}
	ValueFlow::Init(S,T,T);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int flag=0;
			if(st[i][j])
				ValueFlow::add_edge(S,(i-1)*m+j,1,0),flag++;
			if(ed[i][j])
				ValueFlow::add_edge((i-1)*m+j+n*m,T,1,0),flag++;
			ValueFlow::add_edge((i-1)*m+j,(i-1)*m+j+n*m,(ct[i][j]+flag)/2,1);
			int x,y;
			for(int d=0;d<8;d++)
			{
				x=i+dir[d][0],y=j+dir[d][1];
				if(x<=0||y<=0||x>n||y>m)continue;
				ValueFlow::add_edge((i-1)*m+j+n*m,(x-1)*m+y,1000,0);
			}
		}
	int f,a;
	ValueFlow::getValueFlow(f,a);
	if(f==cnt1)printf("%d\n",a-cnt1);
	else
	{
		printf("-1\n");
	}
	return 0;
}
