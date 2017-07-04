#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#define MAXN 20002000
using namespace std;
int Q,L,R,order[100100][2],cnts[MAXN];
bool vis[MAXN];
int main()
{
	int maxr=0;
	scanf("%d",&Q);
	for(int i=1;i<=Q;i++)
	{
		scanf("%d%d",&order[i][0],&order[i][1]);
		maxr=max(maxr,order[i][1]);
	}
	vis[1]=1;
	int n=sqrt(maxr);
	for(int i=2;i<=n;i++)
		if(!vis[i])
		{
			for(int j=i*i;j<=maxr;j+=i)
				vis[j]=1;
		}
	for(int i=2;i<=maxr;i++)
	{
		cnts[i]=cnts[i-1];
		cnts[i]+=(!vis[i]);
	}
	for(int i=1;i<=Q;i++)
		printf("%d\n",cnts[order[i][1]]-cnts[order[i][0]-1]);
	return 0;
}
