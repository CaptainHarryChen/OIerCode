#include<cstdio>
#include<map>
#include<vector>
using namespace std;
const int MAXN=1000005;

int n;
vector<int> adj[MAXN];
int dep[MAXN];

void dfs(int u,int fa=0,int deep=1)
{
	dep[u]=deep;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i];
		if(v==fa)
			continue;
		dfs(v,u,deep+1);
	}
}

map<int,int> cnt[MAXN];
int useid[MAXN],nowid,best[MAXN],bestdep[MAXN];

void solve(int u,int fa=0)
{
	int mxsz=-1,mxid=-1;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i];
		if(v==fa)
			continue;
		solve(v,u);
		if(mxsz<(int)cnt[useid[v]].size())
		{
			mxsz=cnt[useid[v]].size();
			mxid=v;
		}
	}
	if(mxid==-1)
		useid[u]=++nowid;
	else
	{
		useid[u]=useid[mxid];
		best[u]=best[mxid];
		bestdep[u]=bestdep[mxid];
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i];
			if(v==fa||v==mxid)
				continue;
			for(map<int,int>::iterator it=cnt[useid[v]].begin();it!=cnt[useid[v]].end();it++)
			{
				cnt[useid[u]][it->first]+=it->second;
				int t=cnt[useid[u]][it->first];
				if(t>best[u]||(t==best[u]&&bestdep[u]>it->first))
					best[u]=t,bestdep[u]=it->first;
			}
			cnt[useid[v]].clear();
		}
	}
	cnt[useid[u]][dep[u]]++;
	int tt=cnt[useid[u]][dep[u]];
	if(tt>best[u]||(tt==best[u]&&bestdep[u]>dep[u]))
		best[u]=tt,bestdep[u]=dep[u];
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	
	dfs(1);
	
	solve(1);
	
	for(int i=1;i<=n;i++)
		printf("%d\n",bestdep[i]-dep[i]);
	
	return 0;
}
