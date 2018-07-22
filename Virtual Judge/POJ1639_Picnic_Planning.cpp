#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=22,MAXE=MAXN*MAXN;

struct Edge
{
	int u,v,len;
	Edge(){}
	Edge(int _u,int _v,int _len)
	{u=_u;v=_v;len=_len;}
	bool operator < (const Edge &t)const
	{return len<t.len;}
};
struct AdjEdge
{
	int v,len,id;
	AdjEdge(){}
	AdjEdge(int _v,int _len,int _id)
	{v=_v;len=_len;id=_id;}
};

int dsu[MAXN];
int Root(int x)
{
	if(dsu[x]==0)
		return x;
	return (dsu[x]=Root(dsu[x]));
}

int n,m,K;
Edge edge[MAXE];

vector<AdjEdge> adj[MAXN];
void AddEdge(int i)
{
	Edge e=edge[i];
	adj[e.u].push_back(AdjEdge(e.v,e.len,i));
	adj[e.v].push_back(AdjEdge(e.u,e.len,i));
}

int Kruskal()
{
	sort(edge+1,edge+m+1);
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		if(edge[i].u==1||edge[i].v==1)
			continue;
		int r1=Root(edge[i].u),r2=Root(edge[i].v);
		if(r1==r2)
			continue;
		AddEdge(i);
		dsu[r1]=r2;
		ans+=edge[i].len;
	}
	return ans;
}

bool del[MAXE];
int dp[MAXN],dpid[MAXN];
void DP(int u,int f=0)
{
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i].v,eid=adj[u][i].id,len=adj[u][i].len;
		if(v==f||del[eid])
			continue;
		if(u!=1)
		{
			if(dp[u]>len)
				dp[v]=dp[u],dpid[v]=dpid[u];
			else
				dp[v]=len,dpid[v]=eid;
		}
		else
			dp[v]=0;
		DP(v,u);
	}
}

map<string,int> id;

int blkc;
int minE[MAXN];

int main()
{
	id["Park"]=++n;
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		string u,v;
		int len;
		cin>>u>>v>>len;
		if(id.count(u)==0)
			id[u]=++n;
		if(id.count(v)==0)
			id[v]=++n;
		edge[i]=Edge(id[u],id[v],len);
	}
	cin>>K;
	
	int ans=Kruskal();
	
	for(int i=1;i<=m;i++)
	{
		if(edge[i].u!=1&&edge[i].v!=1)
			continue;
		int v=(edge[i].u==1?edge[i].v:edge[i].u);
		int r=Root(v);
		if(minE[r]==0)
		{
			blkc++;
			minE[r]=i;
		}
	}
	for(int i=1;i<=n;i++)
		if(minE[i]!=0)
		{
			ans+=edge[minE[i]].len;
			AddEdge(minE[i]);
		}
	
	for(int i=blkc+1;i<=K;i++)
	{
		DP(1);
		int best=0x3F3F3F3F,e,e1;
		for(int j=1;j<=m;j++)
		{
			if(del[j]||(edge[j].u!=1&&edge[j].v!=1))
				continue;
			int v=(edge[j].u==1?edge[j].v:edge[j].u);
			if(best>edge[j].len-dp[v])
				best=edge[j].len-dp[v],e=dpid[v],e1=j;
		}
		if(best>=0)
			break;
		ans+=best;
		AddEdge(e1);
		del[e]=true;
	}
	
	cout<<"Total miles driven: "<<ans<<endl;
	
	return 0;
}
