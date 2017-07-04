#include<cstdio>
#include<cstring>
#define MAXN 105
int c1[MAXN],c2[MAXN];
int fru[MAXN][2];
int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m)==2)
	{
		memset(fru,0,sizeof fru);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&fru[i][0],&fru[i][1]);
		memset(c1,0,sizeof c1);
		for(int i=fru[1][0];i<=fru[1][1];i++)
			c1[i]=1;
		for(int i=2;i<=n;i++)
		{
			memset(c2,0,sizeof c2);
			for(int j=0;j<=m;j++)
				for(int k=fru[i][0];k+j<=m&&k<=fru[i][1];k++)
					c2[j+k]+=c1[j];
			memcpy(c1,c2,sizeof c1);
		}
		printf("%d\n",c1[m]);
	}
	return 0;
}
