#include<cstdio>
int n,m,a[105],used[260];
bool vis[26000];
void dfs(int k,int s,int l)
{
	vis[s]=1;
	if(k>n)return;
	for(int i=l;i<=m;i++)
		if(used[a[i]])
		{
			used[a[i]]--;
			dfs(k+1,s+a[i],i);
			used[a[i]]++;
		}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&a[i]);
		used[a[i]]=n;
	}
	dfs(1,0,0);
	int i;
	for(i=1;vis[i];i++);
	printf("%d\n",i-1);
	return 0;
}
