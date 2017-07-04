#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#define MAXN 1000100
using namespace std;
int num[MAXN],n,m,maxs;
int get_sum(int x)
{
	maxs=0;
	int cnt=0,sum=0;
	for(int i=1;i<=n;i++)
	{
		if(sum+num[i]<=x)
			sum+=num[i];
		else
		{
			maxs=max(maxs,sum);
			cnt++;
			sum=num[i];
		}
	}
	cnt++;
	maxs=max(maxs,sum);
	if(cnt<m)
		return -2;
	else if(cnt>m)
		return -1;
	return maxs;
}
int main()
{
	int l=0,r=0,mid,s;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&num[i]);
		l=max(l,num[i]);
		r+=num[i];
	}
	while(l<r)
	{
		mid=(l+r)/2;
		s=get_sum(mid);
		if(s==-2)
			r=mid-1;
		else if(s==-1)
			l=mid+1;
		else
			r=mid;
	}
	get_sum(l);
	printf("%d\n",maxs);
}
