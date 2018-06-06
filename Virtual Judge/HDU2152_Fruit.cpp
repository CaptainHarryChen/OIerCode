#include<cstdio>
#include<cstring>
const int MAXN=105;
int c1[MAXN],c2[MAXN];
int A[MAXN],B[MAXN];
int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(int i=1;i<=n;i++)
			scanf("%d%d",A+i,B+i);
		memset(c1,0,sizeof c1);
		c1[0]=1;
		for(int i=1;i<=n;i++)
		{
			memset(c2,0,sizeof c2);
			for(int j=0;j<=m;j++)
				for(int k=A[i];k<=B[i]&&k+j<=m;k++)
					c2[j+k]+=c1[j];
			memcpy(c1,c2,sizeof c1);
		}
		printf("%d\n",c1[m]);
	}
	return 0;
}
