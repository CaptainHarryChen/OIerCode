#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char num[105][105];
int n,v[105],sum,maxv;
bool w[105][105],f[105];
void dfs(int p)
{
	sum+=v[p];
	for(int i=0;i<n;i++)
		if(w[p][i]&&!f[i])
			dfs(i);
	if(sum>maxv)
		maxv=sum;
	sum-=v[p];
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		scanf("%s",num[i]);
		v[i]=strlen(num[i]);
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			if(i==j)continue;
			if(num[i][v[i]-1]==num[j][0])
				w[i][j]=1;
		}
	for(int i=0;i<n;i++)
		if(!f[i])
		{
			sum=0;
			dfs(i);
		}
	printf("%d\n",maxv);
	return 0;
}
