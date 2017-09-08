#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=105;
bool E[MAXN][MAXN];
int S,T,n;
int dfn[MAXN],dfc,low[MAXN],ans=0x7FFFFFFF;
bool dfs(int id,int fa=-1)
{
	dfn[id]=++dfc;
	low[id]=dfn[id];
	bool flag=(id==T);
	for(int i=1;i<=n;i++)
		if(E[id][i])
		{
			if(!dfn[i])
			{
				if(dfs(i,id)&&id!=S)
				{
					flag=1;
					if(low[i]>=dfn[id])
						ans=min(ans,id);
				}
				low[id]=min(low[id],low[i]);
			}
			else if(i!=fa)
				low[id]=min(low[id],dfn[i]);
		}
	return flag;
}
int main()
{
	int a,b;
	scanf("%d",&n);
	while(true)
	{
		scanf("%d%d",&a,&b);
		if(!a&&!b)
			break;
		E[a][b]=1;
		E[b][a]=1;
	}
	scanf("%d%d",&S,&T);
	if(S==T)
		printf("No solution\n");
	else
		dfs(S);
	if(ans==0x7FFFFFFF)
		printf("No solution\n");
	else
		printf("%d\n",ans);
	return 0;
}
