#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 305
#define MAXM 10005
int N,M;
int dis[MAXN][MAXN];
int c[MAXN];
int main()
{
	memset(dis,0x3F,sizeof dis);
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
		dis[i][i]=0;
	for(int i=1;i<=M;i++)
	{
		int k;
		scanf("%d",&k);
		for(int j=1;j<=k;j++)
		{
			scanf("%d",c+j);
			for(int p=j-1;p>0;p--)
				dis[c[j]][c[p]]=dis[c[p]][c[j]]=1;
		}
	}
	for(int k=1;k<=N;k++)
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	int mn=0x7FFFFFFF;
	for(int i=1;i<=N;i++)
	{
		int sum=0;
		for(int j=1;j<=N;j++)
			if(i!=j)
				sum+=dis[i][j];
		mn=min(mn,sum);
	}
	printf("%d\n",mn*100/(N-1));
	return 0;
}
