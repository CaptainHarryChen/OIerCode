#include<cstdio>
#include<algorithm>
using namespace std;
const long long MAXN=1005,MAXM=1005,MAXK=1005,MOD=1000000007;

long long gcd(long long a,long long b)
{return b==0?a:gcd(b,a%b);}
long long powmod(long long a,long long b)
{
	long long ret=1;
	while(b)
	{
		if(b&1LL)
			ret=(1LL*ret*a)%MOD;
		a=(1LL*a*a)%MOD;
		b>>=1LL;
	}
	return ret;
}

struct Edge
{
	long long v,id;
	Edge *nxt;
}E[MAXM*2],*adj[MAXN],*ecnt=E;
void AddEdge(long long u,long long v,long long id)
{
	ecnt->v=v;ecnt->id=id;
	ecnt->nxt=adj[u];
	adj[u]=ecnt++;
	ecnt->v=u;ecnt->id=id;
	ecnt->nxt=adj[v];
	adj[v]=ecnt++;
}

long long ans=1,powk[MAXK],inv[MAXK],fac[MAXK],ifac[MAXK];
long long N,M,K;
long long dfc,dfn[MAXN],low[MAXN],top;
bool vis[MAXM],mk[MAXN];
Edge *stk[MAXM];

void tarjan(long long u)
{
	dfn[u]=++dfc;
	low[u]=dfn[u];
	for(Edge *p=adj[u];p;p=p->nxt)
		if(!vis[p->id])
		{
			long long v=p->v;
			vis[p->id]=true;
			stk[++top]=p;
			if(dfn[v]==0)
			{
				tarjan(v);
				low[u]=min(low[u],low[v]);
				if(low[v]>=dfn[u])
				{
					long long tmp=0,cnt=0;
					bool flag=false;
					for(long long i=top;stk[i+1]!=p&&i>0;i--)
					{
						if(mk[stk[i]->v])
							flag=true;
						mk[stk[i]->v]=true;
						cnt++;
					}
					if(flag)
						tmp=fac[cnt+K-1]*ifac[cnt]%MOD*ifac[K-1]%MOD;	
					else
					{
						for(long long i=0;i<cnt;i++)
							tmp=(tmp+powk[gcd(cnt,i)])%MOD;
						tmp=(tmp*inv[cnt])%MOD;
					}
					
					ans=ans*tmp%MOD;
					do
					{
						mk[stk[top]->v]=false;
						top--;
					}while(stk[top+1]!=p);
				}
			}
			else
				low[u]=min(low[u],dfn[v]);
		}
}

int main()
{
	scanf("%lld%lld%lld",&N,&M,&K);
	powk[0]=1;fac[0]=1;ifac[0]=1;inv[0]=1;
	for(long long i=1;i<1000;i++)
	{
		powk[i]=powk[i-1]*K%MOD;
		fac[i]=fac[i-1]*i%MOD;
		inv[i]=powmod(i,MOD-2);
		ifac[i]=powmod(fac[i],MOD-2);
	}
	for(long long i=1;i<=M;i++)
	{
		long long u,v;
		scanf("%lld%lld",&u,&v);
		AddEdge(u,v,i);
	}
	for(long long i=1;i<=N;i++)
		if(!dfn[i])
			tarjan(i);
	printf("%lld\n",ans);
	
	return 0;
}
