#include<iostream>
#include<cstdio>
#include<cstring>
#define MAXN 1010
using namespace std;
int N,M,K,cx[2*MAXN],cy[2*MAXN];
bool vis[2*MAXN];
struct member
{
	int v;
	member *next;
	member(){v=0;next=NULL;}
	member(int x){v=x;next=NULL;}
}m[2*MAXN];
bool dfs(int u)
{
	for(member*p=m[u].next;p;p=p->next)
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
	cin>>N>>M>>K;
	member *p;
	for(int i=1,a,b;i<=K;i++)
	{
		scanf("%d%d",&a,&b);
		b+=N;
		p=new member(b);
		p->next=m[a].next;
		m[a].next=p;
	}
	memset(cx,-1,sizeof cx);
	memset(cy,-1,sizeof cy);
	int ans=0;
	for(int i=1;i<=N;i++)
		if(cx[i]==-1)
		{
			memset(vis,0,sizeof vis);
			ans+=dfs(i);
		}
	cout<<N+M-ans<<endl;
	return 0;
}
