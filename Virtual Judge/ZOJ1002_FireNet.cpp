#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#define MAXN 5
using namespace std;
int N,cx[MAXN*MAXN],cy[MAXN*MAXN],p1=1,p2=2,f1[MAXN][MAXN],f2[MAXN][MAXN];
char map[MAXN][MAXN];
bool vis[MAXN*MAXN];
struct node
{
	int id;
	node *next;
	node(){id=0;next=NULL;}
	node(int x){id=x;next=NULL;}
}b[4*MAXN*MAXN];
bool dfs(int u)
{
	for(node*p=b[u].next;p;p=p->next)
	{
		int v=p->id;
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
void make_block()
{
	node *p;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(map[i][j]=='.')
			{
				int x,y;
				if(f1[i][j])x=f1[i][j];
				else{x=p1;p1=max(p1,p2)+1;}
				if(f2[i][j])y=f2[i][j];
				else{y=p2;p2=max(p1,p2)+1;}
				p=new node(y);
				b[x].id=x;
				p->next=b[x].next;
				b[x].next=p;
				for(int k=j;k<=N&&map[i][k]!='X';k++)f1[i][k]=x;
				for(int k=i;k<=N&&map[k][j]!='X';k++)f2[k][j]=y;
			}
		}
	}
}	
int main()
{
	while(cin>>N&&N)
	{
		p1=1;p2=2;
		memset(f1,0,sizeof f1);
		memset(f2,0,sizeof f2);
		memset(map,0,sizeof map);
		memset(b,0,sizeof b);
		for(int i=0;i<N;i++)
			scanf("%s",map[i]);
		make_block();
		memset(cx,-1,sizeof cx);
		memset(cy,-1,sizeof cy);
		int ans=0;
		for(int i=1;i<=max(p1,p2);i++)
			if(cx[i]==-1&&b[i].id)
			{
				memset(vis,0,sizeof vis);
				ans+=dfs(i);
			}
		printf("%d\n",ans);
	}
	return 0;
}
