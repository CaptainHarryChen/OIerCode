#include<cstdio>
int n,num[10];
bool used[10];
void dfs(int k)
{
	if(k>n)
	{
		for(int i=1;i<n;i++)
			printf("%d ",num[i]);
		printf("%d\n",num[n]);
		return;
	}
	for(int i=1;i<=n;i++)
		if(!used[i])
		{
			used[i]=1;
			num[k]=i;
			dfs(k+1);
			used[i]=0;
		}
}
int main()
{
	scanf("%d",&n);
	dfs(1);
	return 0;
}
