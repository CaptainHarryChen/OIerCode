#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=10005,MOD=1000000007;

int N,P;
int val[MAXN];
vector<int> adj[MAXN];

int dep[MAXN],mdep[MAXN],fa[MAXN],last[MAXN];
bool vis[MAXN];
int Q[2][MAXN],top[2];

void dfs(int u,int f=0,int deep=1)
{
	mdep[u]=dep[u]=deep;
	fa[u]=f;
	for(int i=0;i<(int)adj[u].size();i++)
		if(adj[u][i]!=f&&!vis[adj[u][i]])
		{
			dfs(adj[u][i],u,deep+1);
			mdep[u]=max(mdep[u],mdep[adj[u][i]]);
		}
}

int GetPathFromMid(int mid,int path[])
{
	for(int i=1;i<=N;i++)
		dep[i]=last[i]=vis[i]=0;
	dfs(mid);
	int mxdep=0,mxval=0;
	for(int i=1;i<=N;i++)
		if(val[i]&&(mxdep<dep[i]||(mxdep==dep[i]&&mxval<val[i])))
			mxdep=dep[i],mxval=val[i];
	
	int id=0;
	top[0]=top[1]=0;
	for(int i=1;i<=N;i++)
		if(dep[i]==mxdep&&val[i]==mxval)
			Q[id][++top[id]]=i;
	while(top[id])
	{
		mxval=0;
		for(int i=1;i<=top[id];i++)
		{
			if(Q[id][i]==mid)
				continue;
			int v=fa[Q[id][i]];
			mxval=max(mxval,val[v]);
		}
		for(int i=1;i<=top[id];i++)
		{
			if(Q[id][i]==mid)
				continue;
			int v=fa[Q[id][i]];
			if(val[v]==mxval)
			{
				Q[id^1][++top[id^1]]=v;
				last[v]=Q[id][i];
			}
		}
		top[id]=0;
		id^=1;
	}
	int tt=mid,it=mxdep;
	while(tt)
	{
		path[it--]=val[tt];
		vis[tt]=true;
		tt=last[tt];
	}
	
	for(int i=1;i<=N;i++)
		dep[i]=last[i]=0;
	dfs(mid);
	int step=mxdep;
	id=0;mxval=0;
	top[0]=top[1]=0;
	Q[id][++top[id]]=mid;
	while(top[id])
	{
		path[step++]=val[Q[id][1]];
		mxval=0;
		for(int k=1;k<=top[id];k++)
		{
			int u=Q[id][k];
			for(int i=0;i<(int)adj[u].size();i++)
			{
				int v=adj[u][i];
				if(!vis[v]&&mdep[v]==mdep[u]&&dep[v]==dep[u]+1)
					mxval=max(mxval,val[v]);
			}
		}
		for(int k=1;k<=top[id];k++)
		{
			int u=Q[id][k];
			for(int i=0;i<(int)adj[u].size();i++)
			{
				int v=adj[u][i];
				if(!vis[v]&&mdep[v]==mdep[u]&&val[v]==mxval&&dep[v]==dep[u]+1)
					Q[id^1][++top[id^1]]=v;
			}
		}
		top[id]=0;
		id^=1;
	}
	
	return step-1;
}

int p1[MAXN],p2[MAXN];
void Solve(int test)
{
	int u=1,v;
	dfs(1);
	for(int i=1;i<=N;i++)
		if(dep[i]>dep[u])
			u=i;
	dfs(u);
	v=u;
	for(int i=1;i<=N;i++)
		if(dep[i]>dep[v])
			v=i;
	int len=dep[v],mid1=v,mid2;
	for(int i=1;i<len/2;i++)
		mid1=fa[mid1];
	mid2=fa[mid1];
	
	int s1=GetPathFromMid(mid1,p1);
	int s2=GetPathFromMid(mid2,p2);
	
	bool flag=(s1>=s2);
	if(s1==s2)
		for(int i=1;i<=s1;i++)
		{
			if(p1[i]>p2[i])
			{flag=true;break;}
			if(p1[i]<p2[i])
			{flag=false;break;}
		}
	if(!flag)
		swap(p1,p2),swap(s1,s2);
	int ans=0;
	for(int i=1;i<=s1;i++)
		ans=(1LL*ans*P%MOD+p1[i])%MOD;
	printf("Case #%d: %d\n",test,ans);
	for(int i=1;i<s1;i++)
		printf("%d ",p1[i]);
	printf("%d\n",p1[s1]);
}

int main()
{
	int T;
	scanf("%d",&T);
	for(int test=1;test<=T;test++)
	{
		scanf("%d%d",&N,&P);
		
		for(int i=1;i<=N;i++)
			adj[i].clear(),vis[i]=false;
		
		for(int i=1;i<N;i++)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		for(int i=1;i<=N;i++)
			scanf("%d",&val[i]);
			
		Solve(test);
	}
	
	return 0;
}
