#include<cstdio>
const int MAXN=205,MAXM=MAXN*MAXN;
int vis[MAXM];
int sg[MAXN][MAXN];
int main()
{
	sg[2][2]=sg[3][2]=sg[2][3]=sg[3][3]=0;
	int ti=1;
	for(int i=2;i<MAXN;i++)
		for(int j=2;j<MAXN;j++)
		{
			if(i<=3&&j<=3)continue;
			for(int k=2;k<=i-2;k++)
				vis[sg[k][j]^sg[i-k][j]]=ti;
			for(int k=2;k<=j-2;k++)
				vis[sg[i][k]^sg[i][j-k]]=ti;
			for(int k=0;;k++)
				if(vis[k]!=ti)
				{
					sg[i][j]=k;
					break;
				}
			ti++;
		}
	
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		if(sg[n][m])
			puts("WIN");
		else
			puts("LOSE");
	}
	
	return 0;
}
