#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,s=99999999,cnt;
struct node
{
	int v,lch,rch,fa;
	node(){v=lch=rch=0;}
}arr[105];
bool f[105];
int dfs(int k)
{
	int ss=0;
	f[k]=1;
	if(arr[k].lch&&!f[arr[k].lch-1])
	{
		cnt++;
		ss=ss+cnt*arr[arr[k].lch-1].v+dfs(arr[k].lch-1);
		cnt--;
	}
	if(arr[k].rch&&!f[arr[k].rch-1])
	{
		cnt++;
		ss=ss+cnt*arr[arr[k].rch-1].v+dfs(arr[k].rch-1);
		cnt--;
	}
	if(arr[k].fa&&!f[arr[k].fa-1])
	{
		cnt++;
		ss=ss+cnt*arr[arr[k].fa-1].v+dfs(arr[k].fa-1);
		cnt--;
	}
	f[k]=0;
	return ss;
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		scanf("%d%d%d",&arr[i].v,&arr[i].lch,&arr[i].rch);
		arr[arr[i].lch-1].fa=i+1;
		arr[arr[i].rch-1].fa=i+1;
	}
	for(int i=0;i<n;i++)
	{
		cnt=0;
		memset(f,0,sizeof(f));
		int ss=dfs(i);
		if(ss<s)
			s=ss;
	}
	printf("%d\n",s);
	return 0;
}
