#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define INF 2147483647
#define MAXN 200200
using namespace std;
int arr[MAXN],cnts[MAXN],rd[MAXN],n,cnt,mincnt=INF;
bool vis[MAXN],f[MAXN],ff[MAXN];
void dfs(int x)
{
	while(1)
	{
		x=arr[x];
		cnt++;
		if(f[x])
		{
			if(cnt-cnts[x]<mincnt)
				mincnt=cnt-cnts[x];
			break;
		}
		cnts[x]=cnt;
		f[x]=1;
		vis[x]=1;
	}
}
void del(int x)
{
	vis[x]=1;
	rd[arr[x]]--;
	while(rd[arr[x]]==0)
	{
		x=arr[x];
		vis[x]=1;
		rd[arr[x]]--;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&arr[i]);
		rd[arr[i]]++;
	}
	for(int i=1;i<=n;i++)
		if(vis[i]==0&&rd[i]==0)
			del(i);
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			cnt=0;
			memset(cnts,0,sizeof cnts);
			memset(f,0,sizeof f);
			vis[i]=1;f[i]=1;
			dfs(i);
		}
	printf("%d\n",mincnt);
	return 0;
}
