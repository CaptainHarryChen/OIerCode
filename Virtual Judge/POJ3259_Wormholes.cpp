#include<cstdio>
#include<cstring>
#define min(a,b) (a>b?b:a)
#define MAXN 505
int dis[MAXN][MAXN];
int main()
{
	int F,N,M,W,s,e,t;
	scanf("%d",&F);
	while(F--)
	{
		scanf("%d%d%d",&N,&M,&W);
		memset(dis,0x3f3f3f3f,sizeof dis);
		for(int i=1;i<=N;i++)
			dis[i][i]=0;
		for(int i=1;i<=M;i++)
		{
			scanf("%d%d%d",&s,&e,&t);
			dis[s][e]=min(dis[s][e],t);
			dis[e][s]=min(dis[e][s],t);
		}
		for(int i=1;i<=W;i++)
		{
			scanf("%d%d%d",&s,&e,&t);
			dis[s][e]=min(dis[s][e],-t);
		}
		bool suc=0;
		for(int k=1;k<=N&&!suc;k++)
			for(int i=1;i<=N&&!suc;i++)
			{
				for(int j=1;j<=N&&!suc;j++)
				{
					int t=dis[i][k]+dis[k][j];
					if(t<dis[i][j])
						dis[i][j]=t;
				}
				if(dis[i][i]<0)
					suc=1;
			}
		if(suc)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
