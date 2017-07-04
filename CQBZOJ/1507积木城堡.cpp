#include<cstdio>
#include<iostream>
#include<cstring>
#define INF 2147483647
#define MAXN 105
using namespace std;
int n,h[MAXN][MAXN],f[MAXN][MAXN*MAXN],ans[MAXN][MAXN*MAXN];
int main()
{
	scanf("%d",&n);
	int sum=0,minh=INF;
	for(int i=1;i<=n;i++)
		for(int j=1;;j++)
		{
			scanf("%d",&h[i][j]);
			if(h[i][j]==-1)
			{h[i][0]=j-1;minh=min(sum,minh);sum=0;break;}
			sum+=h[i][j];
		}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=h[i][0];j++)
			for(int k=1;k<=minh;k++)
			{
				if(k<h[i][j])
					f[j][k]=f[j-1][k];
				else if(f[j-1][k]<f[j-1][k-h[i][j]]+h[i][j])
					f[j][k]=f[j-1][k-h[i][j]]+h[i][j];
				else
					f[j][k]=f[j-1][k];
			}
		for(int j=1;j<=minh;j++)
			ans[i][j]=f[h[i][0]][j];
	}
	for(int i=minh;i>=0;i--)
	{
		bool ff=1;
		for(int j=1;j<=n;j++)
			if(ans[j][i]!=i)
			{ff=0;break;}
		if(ff)
		{printf("%d\n",i);return 0;}
	}
	printf("0\n");
	return 0;
}
