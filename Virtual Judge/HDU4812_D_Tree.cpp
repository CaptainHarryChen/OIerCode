#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005,MOD=1000003;

int inv[MOD+5];
void init_inv()
{
	inv[1]=1;
	for(int i=2;i<MOD;i++)
		inv[i]=(int)((1LL*((MOD-MOD/i)%MOD)*inv[MOD%i])%MOD);
}

struct Edge
{
	int v;
	Edge *nxt;
}E[MAXN*2],*V[MAXN],*Ecur;
void add_edge(int u,int v)
{
	Ecur->v=v;
	Ecur->nxt=V[u];
	V[u]=Ecur++;
}
void graph_init()
{
	Ecur=E;
	fill(V,V+MAXN,(Edge*)NULL);
}

int n,K,val[MAXN];
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

int S[MOD],id;
int Sp[MOD];
int stk[MAXN],stk2[MAXN],top;
pair<int,int>ans;
void ergodic(int u,int pa,int mul)
{
	int m=(int)((1LL*K*inv[mul])%MOD);
	if(S[m]==id&&Sp[m]!=u)
		ans=min(ans,make_pair(min(Sp[m],u),max(Sp[m],u)));
	stk[++top]=mul;
	stk2[top]=u;
	for(Edge *p=V[u];p;p=p->nxt)
	{
		int v=p->v;
		if(!vis[v]&&v!=pa)
			ergodic(v,u,(int)((1LL*mul*val[v])%MOD));
	}
}
void solve()
{
	static int que[MAXN],head,tail;
	fill(vis+1,vis+n+1,0);
	head=tail=1;que[1]=1;
	int u,g;
	while(head<=tail)
	{
		id++;
		u=que[head++];
		g=Gravity::get_center(u);
		vis[g]=true;
		S[val[g]]=id;
		Sp[val[g]]=g;
		for(Edge *p=V[g];p;p=p->nxt)
		{
			int v=p->v;
			if(!vis[v])
			{
				top=0;
				ergodic(v,g,val[v]);
				for(int i=1;i<=top;i++)
				{
					stk[i]=(1LL*stk[i]*val[g])%MOD;
					if(S[stk[i]]==id)
						Sp[stk[i]]=min(Sp[stk[i]],stk2[i]);
					else
						Sp[stk[i]]=stk2[i];
					S[stk[i]]=id;
				}
				que[++tail]=v;
			}
		}
	}
}

int main()
{
	int a,b;
	init_inv();
	while(scanf("%d%d",&n,&K)!=EOF)
	{
		for(int i=1;i<=n;i++)
			scanf("%d",val+i);
		graph_init();
		for(int i=1;i<n;i++)
		{
			scanf("%d%d",&a,&b);
			add_edge(a,b);
			add_edge(b,a);
		}
		ans=make_pair(0x7FFFFFFF,0x7FFFFFFF);
		solve();
		if(ans.first==0x7FFFFFFF&&ans.second==0x7FFFFFFF)
			puts("No solution");
		else
			printf("%d %d\n",ans.first,ans.second);
	}
	return 0;
}
