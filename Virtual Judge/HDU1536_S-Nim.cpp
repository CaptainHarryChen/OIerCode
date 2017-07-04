#include<cstdio>
#include<cstring>
#define MAXN 105
#define MAXS 10005
int take[MAXN],g[MAXS];
bool vis[MAXN];
int main()
{
	int tn,m,n;
	while(1)
	{
		scanf("%d",&tn);
		if(!tn)break;
		for(int i=1;i<=tn;i++)
			scanf("%d",&take[i]);
		memset(g,0,sizeof g);
		for(int i=1,j;i<MAXS;i++)
		{
			memset(vis,0,sizeof vis);
			for(j=1;j<=tn;j++)
				if(i>=take[j])
					vis[g[i-take[j]]]=1;
			for(j=0;vis[j];j++);
			g[i]=j;
		}
		scanf("%d",&m);
		while(m--)
		{
			scanf("%d",&n);
			int s=0,x;
			for(int i=1;i<=n;i++)
			{
				scanf("%d",&x);
				s^=g[x];
			}
			if(s)
				printf("W");
			else
				printf("L");
		}
		printf("\n");
	}
	return 0;
}
