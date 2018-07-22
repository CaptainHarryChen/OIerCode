#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=10005,MAXK=12;

int n,m,k,s,t;
vector<int> adj[MAXN],len[MAXN];

int dis[MAXN][MAXK];
bool inq[MAXN][MAXK];
queue< pair<int,int> > Q;

void SPFA()
{
	memset(dis,0x3F,sizeof dis);
	dis[s][0]=0;
	Q.push(make_pair(s,0));
	while(!Q.empty())
	{
		pair<int,int> z=Q.front();
		Q.pop();
		int u=z.first,e=z.second;
		inq[u][e]=false;
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i];
			if(dis[v][e]>dis[u][e]+len[u][i])
			{
				dis[v][e]=dis[u][e]+len[u][i];
				if(!inq[v][e])
				{
					Q.push(make_pair(v,e));
					inq[v][e]=true;
				}
			}
			if(e<k&&dis[v][e+1]>dis[u][e])
			{
				dis[v][e+1]=dis[u][e];
				if(!inq[v][e+1])
				{
					Q.push(make_pair(v,e+1));
					inq[v][e+1]=true;
				}
			}
		}
	}
}

int main()
{
	scanf("%d%d%d%d%d",&n,&m,&k,&s,&t);
	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		adj[a].push_back(b);
		len[a].push_back(c);
		adj[b].push_back(a);
		len[b].push_back(c);
	}
	
	SPFA();
	
	int ans=0x3F3F3F3F;
	for(int i=0;i<=k;i++)
		ans=min(ans,dis[t][i]);
	printf("%d\n",ans);
	
	return 0;
}
