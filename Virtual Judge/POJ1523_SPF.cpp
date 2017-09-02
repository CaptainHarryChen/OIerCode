#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1005;
bool E[MAXN][MAXN];
int dfn[MAXN],dfc,low[MAXN];
pair<int,int>ans[MAXN];
int tot;
int n;
void dfs(int id,int fa=-1)
{
	dfn[id]=++dfc;
	low[id]=dfn[id];
	int soncnt=0,cnt=1;
	for(int i=1;i<=n;i++)
		if(E[id][i])
		{
			if(!dfn[i])
			{
				soncnt++;
				dfs(i,id);
				low[id]=min(low[id],low[i]);
				if(id!=n&&low[i]>=dfn[id])
					cnt++;
			}
			else if(i!=fa)
				low[id]=min(low[id],dfn[i]);
		}
	if(id==n&&soncnt>1)
		ans[++tot]=make_pair(id,soncnt);
	if(id!=n&&cnt>1)
		ans[++tot]=make_pair(id,cnt);
}
int main()
{
	int a,b;
	for(int Net=1;;Net++)
	{
		memset(E,0,sizeof E);
		n=0;
		scanf("%d",&a);
		if(!a)
			break;
		scanf("%d",&b);
		n=max(n,a);
		n=max(n,b);
		E[a][b]=E[b][a]=1;
		while(true)
		{
			scanf("%d",&a);
			if(!a)
				break;
			scanf("%d",&b);
			E[a][b]=E[b][a]=1;
			n=max(n,a);
			n=max(n,b);
		}
		memset(dfn,0,sizeof dfn);
		dfc=0;
		tot=0;
		dfs(n);
		sort(ans+1,ans+tot+1);
		printf("Network #%d\n",Net);
		if(tot==0)
			printf("  No SPF nodes\n");
		else
			for(int i=1;i<=tot;i++)
				printf("  SPF node %d leaves %d subnets\n",ans[i].first,ans[i].second);
		puts("");
	}
	return 0;
}
