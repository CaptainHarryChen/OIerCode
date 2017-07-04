#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
#define MAXN 200
int K,N,p[MAXN];
bool vis[MAXN];
struct cow{int v,id;}num[MAXN];
bool cmp(cow a,cow b){return a.v>b.v;}
int main()
{
	scanf("%d",&K);
	N=K*3;
	for(int i=1;i<=N;i++)
	{scanf("%d",&num[i].v);num[i].v-=500;num[i].id=i;}
	sort(num+1,num+N+1,cmp);
	int i=1,j=K+1,sum1=0,sum2=0;
	for(int i=1;i<=K;i++)
		sum1+=num[i].v;
	for(int i=K+1;i<=2*K;i++)
		sum2+=num[i].v;
	while(1)
	{
		if(sum1>0&&sum2>0)break;
		i=rand()%K+1;
		j=rand()%K+K+1;
		sum1=sum1-num[i].v+num[j].v;
		sum2=sum2-num[j].v+num[i].v;
		swap(num[i],num[j]);
		i=i==K?1:i+1;
		j=j==K*2?K+1:j+1;
	}
	for(int i=1;i<=N;i++)
		printf("%d\n",num[i].id);
	return 0;
}
