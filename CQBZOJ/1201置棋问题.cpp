#include<cstdio>
#include<iostream>
using namespace std;
int m,n,cnts[15],maxk;
bool arr[15][15],f1[15],f2[15];
void dfs(int k,int a,int b)
{
	maxk=max(maxk,k-1);
	cnts[k-1]++;
	for(int i=a;i<=m;i++)
		for(int j=(i==a?b+1:1);j<=n;j++)
			if(arr[i][j]&&!f1[i]&&!f2[j])
			{
				f1[i]=f2[j]=1;
				dfs(k+1,i,j);
				f1[i]=f2[j]=0;
			}
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&arr[i][j]);
	dfs(1,1,1);
	printf("%d\n",maxk);
	for(int i=1;i<=maxk;i++)
		printf("%d:%d\n",i,cnts[i]);
	return 0;
}
