#include<cstdio>
#include<iostream>
#include <algorithm>
#include<cstring>
using namespace std;
struct side
{
	int a,b,w;
}arr[5000];
int n,m,min2=9999999,jihe[105];
int root(int x,int&h)
{
	while(jihe[x]!=-1)
	{
		x=jihe[x];
		h++;
	}
	return x;
}
bool hebing(int x,int y)
{
	int h1,h2;
	int r1=root(x,h1),r2=root(y,h2);
	if(r1==r2)return 0;
	if(h1<h2)
		jihe[r1]=r2;
	else
		jihe[r2]=r1;
	return 1;
}
bool panduan(side a,side b)
{
	return a.w<b.w;
}
int chuli(int x)
{
	int i=n-1,q=x,max2;
	while(i>0)
	{
		if(q>=m)return -1;
		side k=arr[q];
		if(hebing(k.a,k.b))
		{i--;max2=k.w;}
		q++;
	}
	return max2-arr[x].w;
}
int main()
{
	scanf("%d%d",&n,&m);
	while(n!=0||m!=0)
	{
		min2=9999999;
		memset(arr,0,sizeof(arr));
		for(int i=0;i<m;i++)
			scanf("%d%d%d",&arr[i].a,&arr[i].b,&arr[i].w);
		sort(arr,arr+m,panduan);
		for(int i=0;i<=m-(n-1);i++)
		{
			memset(jihe,255,sizeof(jihe));
			int u=chuli(i);
			if(u==-1)break;
			if(min2>u)
				min2=u;
		}
		if(min2==9999999) printf("-1\n");
		else printf("%d\n",min2);
		scanf("%d%d",&n,&m);
	}
	return 0;
}
/*
4 5
1 2 3
1 3 5
1 4 6
2 4 6
3 4 7
4 6
1 2 10
1 3 100
1 4 90
2 3 20
2 4 80
3 4 40
2 1
1 2 1
3 0
3 1
1 2 1
3 3
1 2 2
2 3 5
1 3 6
5 10
1 2 110
1 3 120
1 4 130
1 5 120
2 3 110
2 4 120
2 5 130
3 4 120
3 5 110
4 5 120
5 10
1 2 9384
1 3 887
1 4 2778
1 5 6916
2 3 7794
2 4 8336
2 5 5387
3 4 493
3 5 6650
4 5 1422
5 8
1 2 1
2 3 100
3 4 100
4 5 100
1 5 50
2 5 50
3 5 50
4 1 150
0 0
*/