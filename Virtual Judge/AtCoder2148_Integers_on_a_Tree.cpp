#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=100005,INF=0x3F3F3F3F;

int N,K;
vector<int> adj[MAXN];
pair<int,int> range[MAXN];
pair<int,int> paint[MAXN];
int ans[MAXN];
queue<int> Q;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > Q0;

int main()
{
	scanf("%d",&N);
	for(int i=1;i<N;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	scanf("%d",&K);
	for(int i=1;i<=N;i++)
		range[i]=make_pair(-INF,INF);
	for(int i=1;i<=K;i++)
	{
		scanf("%d%d",&paint[i].first,&paint[i].second);
		range[paint[i].first]=make_pair(paint[i].second,paint[i].second);
		Q0.push(make_pair(0,paint[i].first));
	}
	while(!Q0.empty())
	{
		pair<int,int> t=Q0.top();
		Q0.pop();
		int fa=t.second;
		if(range[fa].second-range[fa].first<t.first)
			continue;
		for(int i=0;i<(int)adj[fa].size();i++)
		{
			int u=adj[fa][i];
			if(range[u].first!=-INF)
			{
				if(range[u].first%2==range[fa].first%2)
				{
					puts("No");
					return 0;
				}
				if(range[fa].second+1<range[u].first||range[u].second<range[fa].first-1)
				{
					puts("No");
					return 0;
				}
				if(range[fa].first-1<=range[u].first&&range[u].second<=range[fa].second+1)
					continue;
			}
			range[u].first=max(range[u].first,range[fa].first-1);
			range[u].second=min(range[u].second,range[fa].second+1);
			Q0.push(make_pair(range[u].second-range[u].first,u));
		}
	}
	puts("Yes");
	
	for(int i=1;i<=N;i++)
		if(range[i].first==range[i].second)
		{
			ans[i]=range[i].first;
			Q.push(i);
		}
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i];
			if(range[v].first==range[v].second)
				continue;
			if(range[v].second>=ans[u]+1)
				ans[v]=ans[u]+1;
			else
				ans[v]=ans[u]-1;
			range[v].first=range[v].second=ans[v];
			Q.push(v);
		}
	}
	for(int i=1;i<=N;i++)
		printf("%d\n",ans[i]);
	
	return 0;
}
