#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
int n,a[1000][1000],c[1000000],q;
void dfs(int k)
{
	for(int i=0;i<n;i++)
		if(a[k][i]==1)
		{
			a[k][i]=0;
			a[i][k]=0;
			dfs(i);
		}
	c[q++]=k;
}
int main()
{
	cin>>n;
	bool f=0;
	int p=0,b=9999999;
	for(int i=0;i<n;i++)
	{
		f=0;
		for(int j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
			if(a[i][j]==1)
				f=!f;
		}
		if(f)
		{
			if(i<b)b=i;
			p++;
		}
	}
	if(p==0)
		dfs(0);
	else if(p==2)
		dfs(b);
	else
	{
		printf("No Solution!");
		return 0;
	}
	for(int i=q-1;i>0;i--)
		printf("%d ",c[i]+1);
	printf("%d\n",c[0]+1);
	return 0;
}
