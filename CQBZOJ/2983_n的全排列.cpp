#include<cstdio>
#include<iostream>
using namespace std;
int n;
int num[25],f[25];
void dfs(int k)
{
	if(k==n+1)
	{
		for(int i=1;i<=n;i++)
			printf("%d",num[i]);
		printf("\n");
	}
	for(int i=1;i<=n;i++)
	{
		if(f[i])continue;
		num[k]=i;
		f[i]=1;
		dfs(k+1);
		f[i]=0;
		num[k]=0;
	}
}
int main()
{
	scanf("%d",&n);
	dfs(1);
	return 0;
}
