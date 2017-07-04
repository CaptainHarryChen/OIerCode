#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define MAXN 200010
const int dd[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
int n,ans,value;
bool vis[MAXN];
struct farm{int x,y,v;}arr[MAXN];
bool cmp(farm a,farm b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
int find(int x,int y,int l,int r)
{
	if(l>r)return -1;
	int mid=(l+r)>>1;
	if(arr[mid].x==x&&arr[mid].y==y)
		return mid;
	if(arr[mid].x<x||(arr[mid].x==x&&arr[mid].y<y))
		return find(x,y,mid+1,r);
	return find(x,y,l,mid-1);
}
void dfs(int k)
{
	value+=arr[k].v;
	int x=arr[k].x,y=arr[k].y;
	for(int i=0,tx,ty,tk;i<4;i++)
	{
		tx=x+dd[i][0],ty=y+dd[i][1];
		tk=find(tx,ty,1,n);
		if(tk==-1||vis[tk])continue;
		vis[tk]=1;
		dfs(tk);
	}
}
int main()
{
	while(1)
	{
		ans=0;
		memset(vis,0,sizeof vis);
		scanf("%d",&n);
		if(n==0)break;
		for(int i=1;i<=n;i++)
			scanf("%d%d%d",&arr[i].x,&arr[i].y,&arr[i].v);
		sort(arr+1,arr+n+1,cmp);
		for(int i=1;i<=n;i++)
			if(!vis[i])
			{
				value=0;
				vis[i]=1;
				dfs(i);
				ans=max(value,ans);
			}
		printf("%d\n",ans);
	}
	return 0;
}
