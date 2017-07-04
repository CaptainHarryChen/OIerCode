#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int n,p;
struct node
{
	int lch,rch,fa;
	char v;
	node(){v=lch=rch=fa=-1;}
}arr[2200];
bool f[2200];
void FBI(int x,int y)
{
	if(y-x==1)
		return;
	for(int i=x;i<y;i+=2)
	{
		if(arr[i].v=='I'&&arr[i+1].v=='I')
			arr[p].v='I';
		else if(arr[i].v=='B'&&arr[i+1].v=='B')
			arr[p].v='B';
		else
			arr[p].v='F';
		arr[i].fa=p;
		arr[i+1].fa=p;
		arr[p].lch=i;
		arr[p].rch=i+1;
		p++;
	}
	FBI(y,y+(y-x)/2);
}
void dfs(int k)
{
	if(f[k]==1)
        return;
    if(arr[k].lch!=-1)dfs(arr[k].lch);
    if(arr[k].rch!=-1)dfs(arr[k].rch);
    f[k]=1;
	printf("%c",arr[k].v);
}
int main()
{
	cin>>n;
	int len=pow(2,n),a;
	for(int i=0;i<len;i++)
	{
		scanf("%01d",&a);
		if(a==1)
			arr[p].v='I';
		else
			arr[p].v='B';
		p++;
	}
	FBI(0,len);
	int i;
	for(i=0;arr[i].fa!=-1;i++);
	dfs(i);
	printf("\n");
	return 0;
}
