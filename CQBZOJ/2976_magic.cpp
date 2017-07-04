#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define INF 2147483647
#define MAXN 45
using namespace std;
int num[MAXN][MAXN],n;
int main()
{
	scanf("%d",&n);
	int x=1,y=n/2+1;
	num[x][y]=1;
	for(int k=2;k<=n*n;k++)
	{
		if(x==1&&y!=n)
		{x=n;y++;}
		else if(x!=1&&y==n)
		{x--;y=1;}
		else if(x==1&&y==n)
			x++;
		else if(x!=1&&y!=n)
		{
			if(num[x-1][y+1]==0)
			{x--;y++;}
			else
				x++;
		}
		num[x][y]=k;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n-1;j++)
			printf("%d ",num[i][j]);
		printf("%d\n",num[i][n]);
	}
	return 0;
}
