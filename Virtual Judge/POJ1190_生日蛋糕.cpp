//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
using namespace std;
int V,N,ans=0x7FFFFFFF,mins[23],minv[23];
void get_min_S()
{
	for(int i=1;i<=N;i++)
		mins[i]=mins[i-1]+2*i*i;
}
void get_min_V()
{
	for(int i=1;i<=N;i++)
		minv[i]=minv[i-1]+i*i*i;
}
int get_max_V(int n,int r,int h)
{
	int maxv=0;
	for(int i=1;i<=n;i++)
		maxv+=(r-i)*(r-i)*(h-i);
	return maxv;
}
void dfs(int n,int v,int s,int r,int h)
{
	if(n==0)
	{
		if(v==0)
			ans=min(ans,s);
		return;
	}
	if(s+mins[n]>=ans)return;
	if(s+2*v/r>=ans)return;
	for(int r1=r-1,h1;r1>=n;r1--)
		for(h1=h-1;h1>=n;h1--)
		{
			if(v-r1*r1*h1<minv[n-1])continue;
			if(v-r1*r1*h1>get_max_V(n-1,r,h))return;
			dfs(n-1,v-r1*r1*h1,s+2*r1*h1,r1,h1);
		}
}
int main()
{
	scanf("%d%d",&V,&N);
	get_min_S();
	get_min_V();
	for(int r=N;r*r<=V;r++)
		for(int h=N;h<=V;h++)
			dfs(N-1,V-r*r*h,r*r+2*r*h,r,h);
	if(ans==0x7FFFFFFF)
		printf("0\n");
	else
		printf("%d\n",ans);
	return 0;
}
