#include<cstdio>
#include<iostream>
using namespace std;
int v[1005],w[1005],f[1005][10005],id[1005],p;
bool ff=1;
int main()
{
	int t,m;
	cin>>m>>t;
	for(int i=1;i<=m;i++)
		scanf("%d%d",&w[i],&v[i]);
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<=t;j++)
			f[i][j]=f[i-1][j];
		for(int j=0;j<=t;j++)
		{
			if((j>=w[i]&&f[i-1][j-w[i]]!=0)||j==w[i])
				f[i][j]=(f[i-1][j-w[i]]+v[i])>(f[i-1][j])?(f[i-1][j-w[i]]+v[i]):(f[i-1][j]);
		}
	}
	int max1=0,k;
	for(int i=0;i<=t;i++)
		if(f[m][i]>max1)
		{
			max1=f[m][i];
			k=i;
		}
	printf("%d\n",max1);
	for(int i=m;i>0;i--)
		if((k>w[i]&&f[i-1][k-w[i]]+v[i]>f[i-1][k])||(k==w[i]&&f[i-1][k-w[i]]==0&&f[i-1][k]==0))
		{
			id[p++]=i;
			k-=w[i];
		}
	for(int i=p-1;i>=0;i--)
		printf("%d %d %d\n",id[i],w[id[i]],v[id[i]]);
	return 0;
}
