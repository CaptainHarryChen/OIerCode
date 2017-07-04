#include<cstdio>
#define MAXN 210
int n,cnt;
bool vis[MAXN];
struct village
{
	int id;
	village *edg;
	village(){edg=NULL;}
}arr[MAXN];
void dfs(int k,int c)
{
	if(c>n){cnt++;return;}
	for(village *p=arr[k].edg;p;p=p->edg)
		if(!vis[p->id])
		{
			vis[p->id]=1;
			dfs(p->id,c+1);
			vis[p->id]=0;
		}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1,x;j<=n;j++)
		{
			scanf("%d",&x);
			if(x)
			{
				village *p;
				p=new village;
				p->id=j;
				p->edg=arr[i].edg;
				arr[i].edg=p;
			}
		}
	for(int i=1;i<=n;i++)
	{
		vis[i]=1;
		dfs(i,2);
		vis[i]=0;
	}
	printf("%d\n",cnt);
	return 0;
}
