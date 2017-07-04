#include<cstdio>
#include<iostream>
using namespace std;
bool f[15];
int a[15],n,m;
void ff(int b)
{
	if(b>m)
	{
		for(int i=1;i<=m;i++)
			printf("%d ",a[i]);
		printf("\n");
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(f[i]==0)
		{
		a[b]=i;
		f[i]=1;
		ff(b+1);
		a[b]=0;
		f[i]=0;
		}
	}
}
int main()
{
	cin>>n>>m;
	ff(1);
	return 0;
}
