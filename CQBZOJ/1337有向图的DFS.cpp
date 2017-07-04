#include<cstdio>
#include<iostream>
using namespace std;
int n,m,s;
bool a[205][205],f[205];
void dfs(int k)
{
	s++;
	f[k]=1;
	if(s==n)printf("%d",k+1);
	else printf("%d ",k+1);
	for(int i=0;i<n;i++)
		if(a[k][i]==1&&f[i]==0)
			dfs(i);
}
int main()
{
	cin>>n>>m;
	int x,y;
	for(int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		a[x-1][y-1]=1;
	}
	for(int i=0;i<n;i++)
		if(f[i]==0)
			dfs(i);
	return 0;
}
