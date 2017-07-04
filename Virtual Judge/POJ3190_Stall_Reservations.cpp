#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
#define MAXN 50005
int N;
struct cow
{
	int s,e,sta,id;
	bool operator < (const cow &t)const
	{return s<t.s;}
}c[MAXN];
struct stall
{
	int id,end;
	stall(int a,int b){id=a;end=b;}
	bool operator < (const stall &t)const
	{return end>t.end;}
};
priority_queue<stall>S;
int ans[MAXN];
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		scanf("%d%d",&c[i].s,&c[i].e);
		c[i].id=i;
	}
	sort(c+1,c+N+1);
	int sta=0;
	for(int i=1;i<=N;i++)
	{
		if(S.empty()||S.top().end>=c[i].s)
		{sta++;c[i].sta=sta;S.push(stall(sta,c[i].e));}
		else
		{
			c[i].sta=S.top().id;
			S.pop();
			S.push(stall(c[i].sta,c[i].e));
		}
	}
	printf("%d\n",sta);
	for(int i=1;i<=N;i++)
		ans[c[i].id]=c[i].sta;
	for(int i=1;i<=N;i++)
		printf("%d\n",ans[i]);
	return 0;
}
