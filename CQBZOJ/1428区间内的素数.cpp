#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#define MAXN 1000100
using namespace std;
bool vis[MAXN];
int p[MAXN],cnt;
int main()
{
	int a,b;
	scanf("%d%d",&a,&b);
	for(int i=2;i<=b;i++)
		if(!vis[i])
		{
			if(i>=a)p[++cnt]=i;
			if(i>sqrt(b))continue;
			for(int j=i*i;j<=b;j+=i)
				vis[j]=1;
		}
	printf("%d\n",cnt);
	int i,j=1;
	for(i=0;i*10+j<=cnt;i++)
	{
		for(j=1;j<10&&i*10+j<cnt;j++)
			printf("%d ",p[i*10+j]);
		printf("%d\n",p[i*10+j]);
		j=1;
	}
	return 0;
}
