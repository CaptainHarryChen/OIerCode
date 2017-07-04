#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
using namespace std;
bool vis[262200];
bool fang[10][10]={//A B C D E F G H I
							{0,0,0,0,0,0,0,0,0,0},
							{0,1,1,0,1,1,0,0,0,0},//1        ABDE
							{0,1,1,1,0,0,0,0,0,0},//2        ABC
							{0,0,1,1,0,1,1,0,0,0},//3        BCEF
							{0,1,0,0,1,0,0,1,0,0},//4        ADG
							{0,0,1,0,1,1,1,0,1,0},//5        BDEFH
							{0,0,0,1,0,0,1,0,0,1},//6        CFI
							{0,0,0,0,1,1,0,1,1,0},//7        DEGH
							{0,0,0,0,0,0,0,1,1,1},//8        GHI
							{0,0,0,0,0,1,1,0,1,1},//9        EFHI
						};
struct Clock
{
	int s,way[50],f[10],cnt[10];
	Clock(){s=0;memset(way,0,sizeof(way));memset(f,0,sizeof(0));memset(cnt,0,sizeof cnt);}
	Clock(int x){s=x;memset(way,0,sizeof(way));memset(f,0,sizeof(0));memset(cnt,0,sizeof cnt);}
}start;
queue<Clock>q;
void check(Clock x)
{
	for(int i=1;i<=9;i++)
		if(x.f[i]!=0)return;
	for(int i=1;i<x.s;i++)printf("%d ",x.way[i]);
	if(x.s)printf("%d\n",x.way[x.s]);
	exit(0);
}
int hash(Clock x)
{
	int m=0;
	for(int i=1;i<=9;i++)
	{m*=4;m+=x.f[i];}
	return m;
}
int main()
{
	for(int i=1;i<=9;i++)
	{
		scanf("%d",&start.f[i]);
		start.f[i]=(start.f[i]%12)/3;
	}
	check(start);
	q.push(start);
	while(!q.empty())
	{
		Clock t1=q.front(),t2;
		q.pop();
		for(int i=1;i<=9;i++)
		{
			if(t1.cnt[i]>3)continue;
			t2=t1;
			t2.s++;t2.cnt[i]++;t2.way[t2.s]=i;
			for(int j=1;j<=9;j++)
			{
				t2.f[j]+=fang[i][j];
				if(t2.f[j]==4)t2.f[j]-=4;
			}
			int x=hash(t2);
			if(!vis[x])
			{
				check(t2);
				vis[x]=1;
				q.push(t2);
			}
		}
	}
	return 0;
}
