#include<cstdio>
#include<iostream>
using namespace std;
int n,m;
struct node
{
	int v,fa,bro,ch;
	node(){v=fa=bro=0;}
}arr[105];
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
		arr[i].v=i+1;
	int a,b;
	for(int i=0;i<m;i++)
	{
		scanf("%d%d",&a,&b);
		arr[b-1].fa=a-1;
		arr[a-1].ch=b-1;
		int q=-1;
		for(node p=arr[arr[a-1].ch];p.bro;p=arr[p.bro])
			q=p.bro;
		if(q==-1)
			arr[q].bro=b-1;
	}
	for(int i=0,cnt=0,q;i<n;i++)
		if(arr[i].fa==0)
		{
			cnt++;
			q=i;
			if(cnt!=1)
				arr[i].fa=q;
		}
	for(int i=0;i<n;i++)
	{
		if(arr[i].bro)
			printf("%d\n",arr[i].bro);
		else
			printf("%d\n",arr[i].fa);
	}
	return 0;
}
