#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=305,INF=0x3F3F3F3F;

int dis[MAXN][MAXN];

int main()
{
	int n,m,t;
	memset(dis,0x3F,sizeof dis);
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		dis[a][b]=c;
	}
	
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(dis[i][k]!=INF&&dis[k][j]!=INF)
					dis[i][j]=min(dis[i][j],max(dis[i][k],dis[k][j]));
	
	while(t--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		if(dis[a][b]==INF)
			puts("-1");
		else
			printf("%d\n",dis[a][b]);
	}
	
	return 0;
}
