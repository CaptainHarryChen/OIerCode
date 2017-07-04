#include<cstdio>
#include<cstring>
#include<queue>
using std::queue;
using std::min;
#define MAXN 1005
#define MAXM 10005
#define MAXV MAXN+10
#define MAXE (2*MAXN+4*MAXM+10)*10
#define INF 0x3F3F3F3F
int N,M;
int s[MAXM],t[MAXM],c[MAXM];
struct Edge
{
	int id,w,v,next;
	int back;
}E[MAXE];
int head[MAXV],_new;
void add_edge(int a,int b,int w,int v)
{
	E[_new].id=b;E[_new].w=w;E[_new].v=v;
	E[_new].next=head[a];
	head[a]=_new;
	_new++;
	E[_new].id=a;E[_new].v=-v;
	E[_new].next=head[b];
	head[b]=_new;
	_new++;
	E[_new-2].back=_new-1;
	E[_new-1].back=_new-2;
}

int dis[MAXV],path[MAXV],path_e[MAXV];
bool vis[MAXV];
int SPFA(int S,int T)
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
        for(int p=head[t];p;p=E[p].next)
            if(E[p].w>0&&dis[E[p].id]>dis[t]+E[p].v)
            {
                dis[E[p].id]=dis[t]+E[p].v;
                path[E[p].id]=t;
				path_e[E[p].id]=p;
                if(!vis[E[p].id])
                {
                    Q.push(E[p].id);
                    vis[E[p].id]=1;
                }
            }
    }
    if(dis[T]==0x3F3F3F3F)
        return 0;
    int x=T,mn=INF;
    while(x!=S)
    {
        mn=min(mn,E[path_e[x]].w);
        x=path[x];
    }
    x=T;
    while(x!=S)
    {
        E[path_e[x]].w-=mn;
		E[E[path_e[x]].back].w+=mn;
        x=path[x];
    }
    return mn;
}
void Flow(int S,int T,int &F,int &C)
{
	int t,flow=0,cost=0;
    while(t=SPFA(S,T),t)
        flow+=t,cost+=dis[T]*t;
	F=flow;C=cost;
}
int main()
{
	_new=1;
	memset(E,0,sizeof E);
	scanf("%d%d",&N,&M);
	int S=N+2,T=N+3;
	int x,last=0;
	for(int i=1;i<=N;i++)
	{
		scanf("%d",&x);
		if(x-last>0)
			add_edge(S,i,x-last,0);
		else if(x-last<=0)
			add_edge(i,T,last-x,0);
		last=x;
	}
	if(0-last<=0)
		add_edge(N+1,T,last-0,0);
	int s,t,c;
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d%d",&s,&t,&c);
		add_edge(s,t+1,INF,c);
	}
	for(int i=1;i<=N;i++)
		add_edge(i+1,i,INF,0);
	int f,ans;
	Flow(S,T,f,ans);
	printf("%d\n",ans);
	return 0;
}
