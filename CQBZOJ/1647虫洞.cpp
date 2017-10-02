#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=505;
int G[MAXN][MAXN];
queue<int>Q;
int N,M,W;
int cnt[MAXN],dis[MAXN];
bool used[MAXN];
bool SPFA()
{
	memset(dis,0x3F,sizeof dis);
	memset(used,0,sizeof used);
	memset(cnt,0,sizeof cnt);
	dis[1]=0;
	cnt[1]=1;
	Q.push(1);
	used[1]=true;
	while(!Q.empty())
	{
		int t=Q.front();
		Q.pop();used[t]=false;
		for(int i=1;i<=N;i++)
			if(dis[i]>dis[t]+G[t][i])
			{
				dis[i]=dis[t]+G[t][i];
				if(!used[i])
				{
					cnt[i]++;
					if(cnt[i]>N)
						return true;
					Q.push(i);
					used[i]=true;
				}
			}
	}
	return false;
}
int main()
{
	int F,s,e,t;
	scanf("%d",&F);
	while(F--)
	{
		memset(G,0x3F,sizeof G);
		scanf("%d%d%d",&N,&M,&W);
		for(int i=1;i<=N;i++)
			G[i][i]=0;
		for(int i=1;i<=M;i++)
		{
			scanf("%d%d%d",&s,&e,&t);
			G[s][e]=min(G[s][e],t);
			G[e][s]=min(G[s][e],t);
		}
		for(int i=1;i<=W;i++)
		{
			scanf("%d%d%d",&s,&e,&t);
			G[s][e]=min(G[s][e],-t);
		}
		if(SPFA())
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
