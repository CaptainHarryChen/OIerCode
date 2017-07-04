#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define MAXN 1010
using namespace std;
int N,h[MAXN],a[MAXN];
bool cmp(int x,int y)
{
	return h[x]<h[y];
}
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",&h[i]);
		a[i]=i;
	}
	sort(a+1,a+N+1,cmp);
	int cnt=0;
	for(int i=1;i<N;i++)
		for(int j=i+1;j<=N;j++)
			cnt+=h[j]<h[i];
	printf("%d\n",cnt);
	return 0;
}
