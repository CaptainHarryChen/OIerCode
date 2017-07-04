#include<cstdio>
#include<iostream>
using namespace std;
int ads(int a){return a<0?-a:a;}
struct zhanjian
{
	int fa,dis,count;
	zhanjian(){fa=-1;dis=0;count=1;}
}arr[30005];
int root(int x)
{
	if(arr[x].fa==-1)return x;
	int temp=root(arr[x].fa);
	arr[x].dis+=arr[arr[x].fa].dis;
	return arr[x].fa=temp;
}
void bin(int x,int y)
{
	int r1=root(x),r2=root(y);
	arr[r1].fa=r2;
	arr[r1].dis+=arr[r2].count;
	arr[r2].count+=arr[r1].count;
}
void check(int x,int y)
{
	int r1=root(x),r2=root(y);
	if(r1!=r2)puts("-1");
	else printf("%d\n",ads(arr[x].dis-arr[y].dis)-1);
}
int main()
{
	int t,a,b;
	char x;
	cin>>t;
	for(int i=0;i<t;i++)
	{
		scanf("%c",&x);
		if(x=='\n')
		{i--;continue;}
		scanf("%d%d",&a,&b);
		if(x=='M')bin(a,b);
		else check(a,b);
	}
}