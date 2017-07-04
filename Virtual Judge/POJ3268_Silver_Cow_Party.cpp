#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define MAXN 1005
int edge[MAXN][MAXN];
int N,M,X;
int dis1[MAXN],dis2[MAXN];
bool vis[MAXN];
queue<int>Q;
int main()
{
	scanf("%d%d%d",&N,&M,&X);
	int s,e,t;
	memset(edge,0x3F,sizeof edge);
	for(int i=1;i<=N;i++)
		edge[i][i]=0;
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d%d",&s,&e,&t);
		edge[s][e]=min(edge[s][e],t);
	}
	memset(dis1,0x3F,sizeof dis1);
	dis1[X]=0;
	Q.push(X);
	vis[X]=1;
	while(!Q.empty())
	{
		int tmp=Q.front();
		Q.pop();vis[tmp]=0;
		for(int i=1;i<=N;i++)
			if(dis1[i]>dis1[tmp]+edge[tmp][i])
			{
				dis1[i]=dis1[tmp]+edge[tmp][i];
				if(!vis[i])
				{
					Q.push(i);
					vis[i]=1;
				}
			}
	}
	memset(dis2,0x3F,sizeof dis2);
	dis2[X]=0;
	Q.push(X);
	vis[X]=1;
	while(!Q.empty())
	{
		int tmp=Q.front();
		Q.pop();vis[tmp]=0;
		for(int i=1;i<=N;i++)
			if(dis2[i]>dis2[tmp]+edge[i][tmp])
			{
				dis2[i]=dis2[tmp]+edge[i][tmp];
				if(!vis[i])
				{
					Q.push(i);
					vis[i]=1;
				}
			}
	}
	int ans=0;
	for(int i=1;i<=N;i++)
		ans=max(ans,dis1[i]+dis2[i]);
	printf("%d\n",ans);
	return 0;
}
