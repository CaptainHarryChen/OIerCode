#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define MAXN 10010
using namespace std;
int n,num[MAXN],x;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
	scanf("%d",&x);
	bool f=0;
	for(int i=1;i<=n;i++)
		if(num[i]==x)
		{num[i]=-1;f=1;}
	if(!f)
	{
		if(x<num[1])
			printf("%d ",x);
		for(int i=1;i<n;i++)
		{
			printf("%d ",num[i]);
			if(num[i]<x&&num[i+1]>x&&!f)
			{f=1;printf("%d ",x);}
		}
		if(!f&&x>num[n])
		{printf("%d %d\n",num[n],x);}
		else
		{printf("%d\n",num[n]);}
	}
	else
	{
		while(num[n]==-1)n--;
		for(int i=1;i<n;i++)
			if(num[i]!=-1)
				printf("%d ",num[i]);
		if(num[n]!=-1)
			printf("%d\n",num[n]);
	}
	return 0;
}
