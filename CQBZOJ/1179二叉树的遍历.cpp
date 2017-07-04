#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,s;
struct node
{
	int v,fa,lch,rch;
	node(){v=fa=lch=rch=0;}
}arr[105];
bool f[105];
void dfs1(int k)
{
	if(arr[k].v==0||f[k]==1)
		return;
	s++;
	f[k]=1;
	if(s==n)
		printf("%d\n",arr[k].v);
	else
		printf("%d ",arr[k].v);
	dfs1(arr[k].lch);
	dfs1(arr[k].rch);
}
void dfs2(int k)
{
	if(arr[k].v==0||f[k]==1)
		return;
	dfs2(arr[k].lch);
	s++;
	f[k]=1;
	if(s==n)
		printf("%d\n",arr[k].v);
	else
		printf("%d ",arr[k].v);
	dfs2(arr[k].rch);
}
void dfs3(int k)
{
	if(arr[k].v==0||f[k]==1)
		return;
	dfs3(arr[k].lch);
	dfs3(arr[k].rch);
	s++;
	f[k]=1;
	if(s==n)
		printf("%d\n",arr[k].v);
	else
		printf("%d ",arr[k].v);
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		arr[i].v=i+1;
	int a,b,c;
	for(int i=0;i<n;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		arr[b-1].fa=a;
		arr[c-1].fa=a;
		arr[a-1].lch=b-1;
		arr[a-1].rch=c-1;
	}
	for(int i=0;i<n;i++)
		if(arr[i].fa==0)
		{
			printf("%d\n",arr[i].v);
			dfs1(i);
			memset(f,0,sizeof(f));
			s=0;
			dfs2(i);
			memset(f,0,sizeof(f));
			s=0;
			dfs3(i);
			break;
		}
	return 0;
}
