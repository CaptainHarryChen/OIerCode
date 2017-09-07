#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=205,MAXS=1005;
struct Edge
{
	int v,cap;
	Edge *next,*back;
}E[(MAXS+MAXN)*2],*V[MAXN],*cur=E;
void add_edge(int u,int v,int c)
{
	Edge *it;
	it=V[u];
	while(it&&it->v!=v)
		it=it->next;
	if(it)
		it->cap+=c;
	else
	{
		cur->v=v;
		cur->cap=c;
		cur->next=V[u];
		cur->back=cur+1;
		V[u]=cur++;
		cur->v=u;
		cur->cap=0;
		cur->next=V[v];
		cur->back=cur-1;
		V[v]=cur++;
	}
}
int lev[MAXN];
Edge *iter[MAXN];
void update(int S,int T)
{
	queue<int>Q;
	memset(lev,-1,sizeof lev);
	Q.push(S);
	lev[S]=0;
	while(!Q.empty())
	{
		int t=Q.front();
		Q.pop();
		for(Edge *p=V[t];p;p=p->next)
			if(p->cap>0&&lev[p->v]==-1)
			{
				lev[p->v]=lev[t]+1;
				Q.push(p->v);
			}
	}
}
int aug(int u,int augco,int T,int n)
{
	if(u==T)
		return augco;
	int delta;
	for(Edge *&p=iter[u];p;p=p->next)
		if(p->cap>0&&lev[p->v]==lev[u]+1)
		{
			delta=aug(p->v,min(augco,p->cap),T,n);
			if(delta>0)
			{
				p->cap-=delta;
				p->back->cap+=delta;
				return delta;
			}
		}
	return 0;
}
int Dinic(int S,int T,int n)
{
	int flow=0,temp;
	while(update(S,T),lev[T]!=-1)
	{
		for(int i=0;i<=n;i++)
			iter[i]=V[i];
		while(temp=aug(S,0x7FFFFFFF,T,n),temp)
			flow+=temp;
	}
	return flow;
}
struct Street
{
	int x,y,d;
}S[MAXS];
int in[MAXN],out[MAXN];
int main()
{
	int T,m,s,x,y,d;
	bool flag;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&m,&s);
		memset(out,0,sizeof out);
		memset(in,0,sizeof in);
		for(int i=1;i<=s;i++)
		{
			scanf("%d%d%d",&x,&y,&d);
			S[i].x=x;
			S[i].y=y;
			S[i].d=d;
			out[x]++;
			in[y]++;
		}
		flag=true;
		for(int i=1;i<=m;i++)
			if((in[i]+out[i])%2==1)
				flag=false;
		if(!flag)
		{
			printf("impossible\n");
			continue;
		}
		cur=E;
		memset(V,0,sizeof V);
		for(int i=1;i<=m;i++)
		{
			if(in[i]>out[i])
				add_edge(0,i,(in[i]-out[i])/2);
			if(in[i]<out[i])
				add_edge(i,m+1,(out[i]-in[i])/2);
		}
		for(int i=1;i<=s;i++)
			if(S[i].d==0)
				add_edge(S[i].y,S[i].x,1);
		Dinic(0,m+1,m+2);
		for(Edge *p=V[0];p;p=p->next)
			if(p->cap)
			{
				flag=false;
				break;
			}
		if(!flag)
			printf("impossible\n");
		else
			printf("possible\n");
	}
	return 0;
}
