#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,s;
struct node
{
	int fa,ch[205],p;
	char v[10];
	node(){fa=p=0;memset(ch,0,sizeof(ch));memset(ch,0,sizeof(ch));}
}arr[205];
bool f[205];
void dfs1(int k)
{
	if(arr[k].v==0||f[k]==1)
		return;
	s++;
	f[k]=1;
	if(s==n)
		printf("%s\n",arr[k].v);
	else
		printf("%s ",arr[k].v);
	for(int i=0;i<arr[k].p;i++)
		dfs1(arr[k].ch[i]);
}
void dfs2(int k)
{
	if(arr[k].v==0||f[k]==1)
		return;
	for(int i=0;i<arr[k].p;i++)
		dfs2(arr[k].ch[i]);
	s++;
	f[k]=1;
	if(s==n)
		printf("%s\n",arr[k].v);
	else
		printf("%s ",arr[k].v);
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		scanf("%s",arr[i].v);
		int x;
		scanf("%d",&x);
		while(x)
		{arr[i].ch[arr[i].p++]=x-1;scanf("%d",&x);}
	}
	for(int i=0;i<n;i++)
		if(arr[i].fa==0)
		{
			dfs1(i);
			memset(f,0,sizeof(f));
			s=0;
			dfs2(i);
			break;
		}
	return 0;
}
