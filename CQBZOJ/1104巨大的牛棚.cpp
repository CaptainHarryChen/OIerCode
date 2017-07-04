#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define INF 2139062143
#define MAXN 1010
int n,t,farm[MAXN][MAXN],maxbarn;
int main()
{
	scanf("%d%d",&n,&t);
	int a,b;
	for(int i=1;i<=t;i++)
	{
		scanf("%d%d",&a,&b);
		farm[a][b]=-1;
	}
	for(int i=2;i<=n;i++)
		for(int j=2;j<=n;j++)
			if(farm[i][j]!=-1)
			{
				farm[i][j]=min(farm[i-1][j],farm[i-1][j-1]);
				farm[i][j]=min(farm[i][j],farm[i][j-1]);
				farm[i][j]++;
				maxbarn=max(farm[i][j],maxbarn);
			}
	printf("%d\n",maxbarn+1);
	return 0;
}
