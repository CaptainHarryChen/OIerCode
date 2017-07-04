#include<cstdio>
#define MAXN 505
bool arr[MAXN][MAXN],vis[MAXN];
int n,m,cnt;
void dfs(int x)
{
	for(int i=1;i<=n;i++)
		if(arr[x][i]&&!vis[i])
		{
			vis[i]=1;
			dfs(i);
		}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		arr[x][y]=1;
		arr[y][x]=1;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			cnt++;
			dfs(i);
		}
	printf("%d\n",cnt);
	return 0;
}
