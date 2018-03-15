#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

namespace ISAP
{
	const int MAX_NODE=20,MAX_EDGE=100,INF=0x7FFFFFFF;
	struct Edge
	{
		int x,w;
		Edge *nxt,*bck;
	}E[MAX_EDGE],*adj[MAX_NODE],*top;
	int S,T,N;
	int dis[MAX_NODE],cnt_d[MAX_NODE];
	void add_edge(int x,int y,int w)
	{
		top->x=y;top->w=w;
		top->nxt=adj[x];
		top->bck=top+1;
		adj[x]=top++;
		top->x=x;top->w=0;
		top->nxt=adj[y];
		top->bck=top-1;
		adj[y]=top++;
	}
	void Init(int s,int t,int n)
	{
		top=E;
		memset(adj,0,sizeof adj);
		S=s;T=t;N=n;
	}
	int aug(int now,int augco)
	{
		if(now==T)return augco;
		int augc=augco,mn=N,delta;
		for(Edge *p=adj[now];p;p=p->nxt)
			if(p->w>0)
			{
				if(dis[p->x]==dis[now]-1)
				{
					delta=min(p->w,augc);
					delta=aug(p->x,delta);
					p->w-=delta;
					p->bck->w+=delta;
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
};

class CosmicBlocks
{
	static const int MAXN=10,INF=0x7FFFFFFF;
	int n,mn,mx,ans;
	vector<int> col,fl[MAXN];
	bool adj[MAXN][MAXN];
	int h[MAXN];
	
	bool check()
	{
		int S=n*2+1,T=n*2+2,S0=n*2+3,T0=n*2+4;
		ISAP::Init(S0,T0,n*2+4);
		int sum=0;
		for(int i=1;i<=n;i++)
		{
			ISAP::add_edge(i,T0,col[i]);
			ISAP::add_edge(S0,i+n,col[i]);
			ISAP::add_edge(i+n,T,INF);
			sum+=col[i];
		}
		for(int i=0;i<(int)fl[1].size();i++)
			ISAP::add_edge(S,fl[1][i],INF);
		ISAP::add_edge(T,S,INF);
		int cnt=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(adj[i][j])
				{
					ISAP::add_edge(j+n,i,INF);
					ISAP::add_edge(S0,i,1);
					ISAP::add_edge(j+n,T0,1);
					cnt++;
				}
		if(ISAP::iSap()==sum+cnt)
			return true;
		return false;
	}
	
	int count_permutation()
	{
		static int per[MAXN],pos[MAXN];
		for(int i=1;i<=n;i++)
			per[i]=i;
		int res=0;
		do
		{
			for(int i=1;i<=n;i++)
				pos[per[i]]=i;
			bool flag=true;
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					if(adj[i][j]&&pos[i]>pos[j])
					{
						flag=false;
						break;
					}
			res+=flag;
		}while(next_permutation(per+1,per+n+1));
		return res;
	}
	
	void enum_adj(int pos)
	{
		int x=(pos-1)/n+1,y=(pos-1)%n+1;
		if(x>n)
		{
			#ifdef DEBUG
			printf("adj:");
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					if(adj[i][j])
						printf("[%d %d]",i,j);
			#endif
			if(check())
			{
				#ifdef DEBUG
				printf("----success:");
				#endif
				
				int c=count_permutation();
				#ifdef DEBUG
				printf("%d",c);
				#endif
				if(mn<=c&&c<=mx)
				{
					ans++;
					#ifdef DEBUG
					printf("-------------------------------------------------------ans:%d\n",ans);
					#endif
				}
				#ifdef DEBUG
				else
					puts("");
				#endif
			}
			#ifdef DEBUG
			else
				puts("");
			#endif
			return;
		}
		adj[x][y]=false;
		enum_adj(pos+1);
		if(h[x]==h[y]+1)
		{
			adj[x][y]=true;
			enum_adj(pos+1);
		}
	}
	
	void enum_height(int i)
	{
		static int cnt[MAXN];
		if(i>n)
		{
			for(int j=1;j<=n;j++)
				cnt[j]=0,fl[j].clear();
			for(int j=1;j<=n;j++)
				cnt[h[j]]+=col[j],fl[h[j]].push_back(j);
			for(int j=2;j<=n;j++)
				if(cnt[j]>cnt[j-1])
					return;
			
			#ifdef DEBUG
			printf("\nheight:");
			for(int i=1;i<=n;i++)
				printf("[%d]",h[i]);
			puts("");
			#endif
			
			enum_adj(1);
			
			return;
		}
		for(int j=1;j<=n;j++)
		{
			h[i]=j;
			enum_height(i+1);
		}
	}
	
	int solve()
	{
		enum_height(1);
		return ans;
	}
	
public:
	int getNumOrders(vector<int> &blockTypes,int minWays,int maxWays)
	{
		n=blockTypes.size();
		col.push_back(0);
		for(int i=0;i<n;i++)
			col.push_back(blockTypes[i]);
		mn=minWays;
		mx=maxWays;
		return solve();
	}
};
