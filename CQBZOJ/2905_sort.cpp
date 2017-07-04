#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<map>
#include<algorithm>
#define MAXN 1010
using namespace std;
map<int,int>m;
int n,c,num[MAXN],cnt,aa[MAXN],cnts[MAXN];
bool ch(int a,int b)
{
	int x=m[a],y=m[b];
	if(cnts[x]>cnts[y])
		return 1;
	else if(cnts[x]==cnts[y])
	{
		if(aa[x]<aa[y])
			return 1;
		else
			return 0;
	}
	return 0;
}
int main()
{
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&num[i]);
		if(m[num[i]]==0)
			m[num[i]]=++cnt;
		if(aa[m[num[i]]]==0)
			aa[m[num[i]]]=i;
		cnts[m[num[i]]]++;
	}
	sort(num+1,num+n+1,ch);
	for(int i=1;i<n;i++)
		printf("%d ",num[i]);
	printf("%d\n",num[n]);
	return 0;
}
