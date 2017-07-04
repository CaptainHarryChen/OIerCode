#include<cstdio>
#include<iostream>
#include<cstring>
#define MAXN 110
using namespace std;
int N,M,K,cx[MAXN],cy[MAXN];
bool vis[MAXN];
struct machine
{
	int v;
	machine *next;
	machine(){v=0;next=NULL;}
	machine(int u){v=u;next=NULL;}
}m[MAXN];
bool dfs(int u)
{
	for(machine *p=m[u].next;p!=NULL;p=p->next)
	{
		int v=p->v;
		if(!vis[v])
		{
			vis[v]=1;
			if(cy[v]==-1||dfs(cy[v]))
			{
				cx[u]=v;cy[v]=u;
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	cin>>N;
	while(N!=0)
	{
		memset(m,0,sizeof m);
		memset(cx,-1,sizeof cx);
		memset(cy,-1,sizeof cy);
		cin>>M>>K;
		int i,x,y;
		machine *p;
		for(int j=1;j<=K;j++)
		{
			scanf("%d%d%d",&i,&x,&y);
			if(x==0||y==0)continue;
			p=new machine(y);
			p->next=m[x].next;
			m[x].next=p;
		}
		int ans=0;
		for(int i=0;i<N;i++)
			if(cx[i]==-1)
			{
				memset(vis,0,sizeof vis);
				ans+=dfs(i);
			}
		cout<<ans<<endl;
		cin>>N;
	}
	return 0;
}