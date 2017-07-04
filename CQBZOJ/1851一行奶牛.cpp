#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>
using namespace std;
#define MAXN 1005
int n,num[MAXN],cnt,ans,len;
map<int,int>color;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&num[i]);
		if(color[num[i]]==0)
			color[num[i]]=++cnt;
	}
	for(int i=1;i<=cnt;i++)
	{
		for(int j=1,k=0;j<=n;j++)
			if(color[num[j]]==i)
				continue;
			else if(color[num[j]]==k)
				len++;
			else
			{ans=max(len,ans);len=1;k=color[num[j]];}
	}
	printf("%d\n",ans);
	return 0;
}
