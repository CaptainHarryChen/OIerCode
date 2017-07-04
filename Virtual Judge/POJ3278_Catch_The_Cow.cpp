#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
#define MAXN 200010
int N,K,step[MAXN];
int bfs(int start,int goal)
{
	if(start==goal)return 0;
	queue<int>Q;
	memset(step,127,sizeof step);
	step[start]=0;
	Q.push(start);
	while(!Q.empty())
	{
		int t=Q.front();
		Q.pop();
		if(step[t+1]>step[t]+1)
		{
			step[t+1]=step[t]+1;
			if(t+1==goal)return step[t+1];
			Q.push(t+1);
		}
		if(step[t-1]>step[t]+1)
		{
			step[t-1]=step[t]+1;
			if(t-1==goal)return step[t-1];
			Q.push(t-1);
		}
		if(t*2<=MAXN&&step[t*2]>step[t]+1)
		{
			step[t*2]=step[t]+1;
			if(t*2==goal)return step[t*2];
			Q.push(t*2);
		}
	}
	return -1;
}
int main()
{
	scanf("%d%d",&N,&K);
	printf("%d\n",bfs(N,K));
	return 0;
}
