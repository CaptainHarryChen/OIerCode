#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005;

template<class T>
void Read(T &x)
{
	char c;
	bool f=0;
	while(c=getchar(),c!=EOF)
	{
		if(c=='-')
			f=1;
		else if(c>='0'&&c<='9')
		{
			x=c-'0';
			while(c=getchar(),c>='0'&&c<='9')
				x=x*10+c-'0';
			if(f)
				x=-x;
			return;
		}
	}
}

struct Edge
{
	int v,val;
	Edge *nxt;
}E[MAXN*2],*V[MAXN],*cur=E;
void add_edge(int u,int v,int val)
{
	cur->v=v;cur->val=val;
	cur->nxt=V[u];
	V[u]=cur++;
}

int N,K,M;
bool vis[MAXN];

namespace Gravity
{
	int val[MAXN],siz[MAXN],stk[MAXN],top;
	void calc_g(int u,int pa)
	{
		stk[++top]=u;
		siz[u]=1;val[u]=0;
		for(Edge *p=V[u];p;p=p->nxt)
		{
			int v=p->v;
			if(v!=pa&&!vis[v])
			{
				calc_g(v,u);
				siz[u]+=siz[v];
				val[u]=max(val[u],siz[v]);
			}
		}
	}
	int get_center(int u)
	{
		top=0;
		calc_g(u,0);
		int res,best=0x7FFFFFFF;
		for(int i=1;i<=top;i++)
		{
			int v=stk[i];
			val[v]=max(val[v],siz[u]-siz[v]);
			if(best>val[v])
			{best=val[v];res=v;}
		}
		return res;
	}
}

namespace BIT
{
	pair<int,int> S[MAXN];
	void insert(int pos,int val,int id)
	{
		pos++;
		while(pos<=K)
		{
			S[pos]=make_pair(id,max(val,S[pos].first==id?S[pos].second:0));
			pos+=(pos&(-pos));
		}
	}
	int get(int pos,int id)
	{
		pos++;
		int res=0;
		while(pos>0)
		{
			res=max(res,S[pos].first==id?S[pos].second:0);
			pos-=(pos&(-pos));
		}
		return res;
	}
}

bool crow[MAXN];
int que[MAXN],head,tail;
pair<int,int> stk[MAXN];
int top;
int id;

int calc(int u,int pa,int cnt,int dis)
{
	int res=max(0,dis+BIT::get(K-cnt,id));
	stk[++top]=make_pair(cnt,dis);
	for(Edge *p=V[u];p;p=p->nxt)
	{
		int v=p->v;
		if(v!=pa&&!vis[v]&&cnt+crow[v]<=K)
			res=max(res,calc(v,u,cnt+crow[v],dis+p->val));
	}
	return res;
}
int solve()
{
	head=tail=1;
	que[1]=1;
	int res=0;
	id=0;
	while(head<=tail)
	{
		id++;
		int u=que[head++];
		int g=Gravity::get_center(u);
		BIT::insert(crow[g],0,id);
		vis[g]=true;
		for(Edge *p=V[g];p;p=p->nxt)
		{
			int v=p->v;
			if(!vis[v]&&K)
			{
				top=0;
				res=max(res,calc(v,g,crow[v],p->val));
				for(int i=1;i<=top;i++)
					BIT::insert(stk[i].first+crow[g],stk[i].second,id);
				que[++tail]=v;
			}
		}
	}
	return res;
}

int main()
{
	Read(N);Read(K);Read(M);
	for(int i=1,id;i<=M;i++)
		Read(id),crow[id]=true;
	for(int i=1,a,b,c;i<N;i++)
	{
		Read(a);Read(b);Read(c);
		add_edge(a,b,c);
		add_edge(b,a,c);
	}
	printf("%d\n",solve());
	return 0;
}
