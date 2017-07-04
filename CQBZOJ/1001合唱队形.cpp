#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int x[105],f[105],g[105];
int main()
{
	int n,sum=0;
	cin>>n;
	for(int i=0;i<n;i++)
		scanf("%d",&x[i]);
	for(int iii=0;iii<n;iii++)
	{
		for(int i=0;i<n;i++)f[i]=g[i]=1;
		for(int i=1;i<iii;i++)
		{
			int max=1;
			for(int j=i;j>=0;j--)
				if(x[j]<x[i]&&f[j]+1>max)
					max=f[j]+1;
			f[i]=max;
		}
		int max1=1;
		for(int i=0;i<iii;i++)
			if(f[i]>max1)
				max1=f[i];
		if(max1==n-1)
		{sum=n;break;}
		for(int i=n-1;i>=iii;i--)
		{
			int max=1;
			for(int j=i;j<n;j++)
				if(x[j]<x[i]&&g[j]+1>max)
					max=g[j]+1;
			g[i]=max;
		}
		int max2=1;
		for(int i=n-1;i>=iii;i--)
			if(g[i]>max2)
				max2=g[i];
		if(max2==n)
		{sum=n;break;}
		if(sum<max1+max2)
			sum=max1+max2;
	}
	printf("%d\n",n-sum);
	return 0;
}
