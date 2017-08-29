#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=50,MAXE=2000;
typedef pair<int,int> Edge;
vector<Edge> V[MAXN];
bool vis[MAXE];
int ans[MAXE],top;
void euler(int id)
{
	int s=V[id].size();
	for(int i=0;i<s;i++)
		if(!vis[V[id][i].first])
		{
			vis[V[id][i].first]=1;
			euler(V[id][i].second);
			ans[++top]=V[id][i].first;
		}
}
int main()
{
	int a,b,c;
	while(true)
	{
		top=0;
		memset(vis,0,sizeof vis);
		for(int i=1;i<MAXN;i++)
			V[i].clear();
		scanf("%d%d",&a,&b);
		if(!a&&!b)
			break;
		scanf("%d",&c);
		V[a].push_back(Edge(c,b));
		V[b].push_back(Edge(c,a));
		while(true)
		{
			scanf("%d%d",&a,&b);
			if(!a&&!b)
				break;
			scanf("%d",&c);
			V[a].push_back(Edge(c,b));
			V[b].push_back(Edge(c,a));
		}
		int S=1,cnt=0;
		for(int i=1;i<MAXN;i++)
		{
			sort(V[i].begin(),V[i].end());
			if(V[i].size()&1)
			{
				cnt++;
				break;
			}
		}
		if(cnt!=0)
		{
			printf("Round trip does not exist.\n");
			continue;
		}
		euler(S);
		for(int i=top;i>0;i--)
			printf("%d ",ans[i]);
		puts("");
	}
	return 0;
}
