#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int x[5005],f[5005];
int main()
{
	int n=0;
	for(n=0;scanf("%d",&x[n])==1;n++)f[n]=1;
	for(int i=1;i<n;i++)
	{
		int maxn=1;
		for(int j=i-1;j>=0;j--)
			if(x[j]>=x[i]&&f[j]+1>maxn)
				maxn=f[j]+1;
		f[i]=maxn;
	}
	int max=0;
	for(int i=0;i<n;i++)
		if(f[i]>max)
			max=f[i];
	printf("%d\n",max);
	for(int i=0;i<n;i++)f[i]=1;
	max=0;
	for(int i=1;i<n;i++)
	{
		int max=1;
		for(int j=i-1;j>=0;j--)
			if(x[j]<x[i]&&f[j]+1>max)
				max=f[j]+1;
		f[i]=max;
	}
	for(int i=0;i<n;i++)
		if(f[i]>max)
			max=f[i];
	printf("%d\n",max);
	return 0;
}
