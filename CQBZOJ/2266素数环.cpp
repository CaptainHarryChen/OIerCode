#include<cstdio>
#include<iostream>
using namespace std;
int n,k,order[12],num[20],cnt,p=1;
bool f[40],vis[20];
void dfs(int m)
{
	if(m==n+1)
	{
		if(!f[num[n]+num[1]])
		{
			cnt++;
			if(cnt==order[p])
			{
				for(int i=1;i<n;i++)
					printf("%d ",num[i]);
				printf("%d\n",num[n]);
				p++;
			}
		}
		return;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]&&!f[i+num[m-1]])
		{
			num[m]=i;
			vis[i]=1;
			dfs(m+1);
			vis[i]=0;
		}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++)
		scanf("%d",&order[i]);
	for(int i=2;i<=n;i++)
		if(!f[i])
			for(int j=i*i;j<=2*n;j+=i)
				f[j]=1;
	num[1]=1;
	vis[1]=1;
	dfs(2);
	printf("%d\n",cnt);
	return 0;
}
