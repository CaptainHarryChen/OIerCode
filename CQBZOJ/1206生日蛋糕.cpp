#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int n,m,MINS=999999999,minv[25],mins[25];
int maxv(int mi,int ri,int hi)
{
	int sum=0;
	for(int i=1;i<=mi;i++)
		sum+=(ri-i)*(ri-i)*(hi-i);
	return sum;
}
void dfs(int mi,int si,int vi,int ri,int hi)
{
	if(mi==0)
	{
		if(vi==0)
			if(si<MINS)
				MINS=si;
		return;
	}
	if(si+mins[mi-1]>=MINS)
		return;//jianzhi 3
	if(si+2*vi/ri>=MINS)
		return;//jianzhi 4
	for(int r=ri-1;r>=mi;r--)
		for(int h=hi-1;h>=mi;h--)
		{
			int v=vi-r*r*h;
			if(v<minv[mi-1])
				continue;//jianzhi 1
			if(v>maxv(mi-1,r,h))
				return;//jianzhi 2
			dfs(mi-1,si+2*r*h,v,r,h);
		}
}
int main()
{
	scanf("%d%d",&n,&m);
	minv[1]=1;
	mins[1]=2;
	for(int i=2;i<=m;i++)
	{
		minv[i]=minv[i-1]+i*i*i;
		mins[i]=mins[i-1]+2*i*i;
	}
	for(int r=m;r<=(int)sqrt((double)n);r++)
		for(int h=m;h<=n;h++)
			dfs(m-1,r*r+2*r*h,n-r*r*h,r,h);
	if(MINS==999999999)
		MINS=0;
	printf("%d\n",MINS);
	return 0;
}
