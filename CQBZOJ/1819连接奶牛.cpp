#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define MAXN 2020
using namespace std;
int N,cow[15][2],cnt;
bool vis[15];
bool check(int i,int x,int y,int f,int &ff)
{
	if(cow[i][0]==x)
	{
		if(cow[i][1]>y)ff=1;
		else ff=2;
	}
	else
	{
		if(cow[i][0]>x)ff=3;
		else ff=4;
	}
	return ff!=f;
}
void dfs(int x,int y,int f,int m)
{
	int ff;
	if(N==m)
	{
		if((x!=0&&y!=0)||!check(0,x,y,f,ff))return;
		cnt++;
		return;
	}
	for(int i=1;i<=N;i++)
	{
		if(vis[i])continue;
		if(cow[i][0]==x||cow[i][1]==y)
		{
			if(!check(i,x,y,f,ff))continue;
			vis[i]=1;
			dfs(cow[i][0],cow[i][1],ff,m+1);
			vis[i]=0;
		}
	}
}
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d%d",&cow[i][0],&cow[i][1]);
	dfs(0,0,0,0);
	printf("%d\n",cnt);
	return 0;
}
