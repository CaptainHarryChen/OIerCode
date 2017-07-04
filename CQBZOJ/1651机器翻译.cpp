#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
queue<int>ram;
bool vis[1005];
int cnt,n,m,f;
int main()
{

	scanf("%d%d",&m,&n);
	int x;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if(vis[x])continue;
		f++;
		if(cnt==m)
		{
			vis[ram.front()]=0;
			vis[x]=1;
			ram.pop();
			ram.push(x);
		}
		else
		{
			vis[x]=1;
			ram.push(x);
			cnt++;
		}
	}
	printf("%d\n",f);
	return 0;
}
