#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005;

struct Edge
{
	int v,dir,id;
	Edge(int _v,int _dir,int _id)
	{v=_v;dir=_dir;id=_id;}
};

int n,m;
vector<Edge> adj[MAXN];
bool vis[MAXN],visE[MAXN];
int col[MAXN],cnt[3];
int vcnt,ecnt;
bool conflict;

void dfs(int u)
{
	vis[u]=true;
	vcnt++;
	cnt[col[u]]++;
	for(auto e:adj[u])
		if(!visE[e.id])
		{
			visE[e.id]=true;
			ecnt++;
			if(!vis[e.v])
			{
				col[e.v]=(col[u]+e.dir+3)%3;
				dfs(e.v);
			}
			else if(col[e.v]!=(col[u]+e.dir+3)%3)
				conflict=true;
		}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		adj[a].push_back(Edge(b,1,i));
		adj[b].push_back(Edge(a,-1,i));
	}
	long long ans=0;
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			cnt[0]=cnt[1]=cnt[2]=0;
			vcnt=ecnt=0;
			conflict=false;
			dfs(i);
			if(conflict)
				ans+=1LL*vcnt*vcnt;
			else if(cnt[0]==0||cnt[1]==0||cnt[2]==0)
				ans+=ecnt;
			else
				ans+=1LL*cnt[0]*cnt[1]+1LL*cnt[1]*cnt[2]+1LL*cnt[0]*cnt[2];
		}
	printf("%lld\n",ans);
	
	return 0;
}
