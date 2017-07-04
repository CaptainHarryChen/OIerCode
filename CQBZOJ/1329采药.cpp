#include<cstdio>
#include<iostream>
using namespace std;
int v[105],w[105],f[105][1005];
int main()
{
	int t,m;
	cin>>t>>m;
	for(int i=1;i<=m;i++)
		scanf("%d%d",&w[i],&v[i]);
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<=t;j++)
			f[i][j]=f[i-1][j];
		for(int j=0;j<=t;j++)
			if((j>=w[i]&&f[i-1][j-w[i]]!=0)||j==w[i])
				f[i][j]=(f[i-1][j-w[i]]+v[i])>(f[i-1][j])?(f[i-1][j-w[i]]+v[i]):(f[i-1][j]);
	}
	int max1=0;
	for(int i=0;i<=t;i++)
		if(f[m][i]>max1)
			max1=f[m][i];
	printf("%d\n",max1);
	return 0;
}
