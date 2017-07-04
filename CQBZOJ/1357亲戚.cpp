#include<cstdio>
#include<iostream>
using namespace std;
int fa[5005];
int root(int n,int *p)
{
	int x=n,i=0;
	while(fa[x]!=-1)
	{
		x=fa[x];
		i++;
	}
	*p=i;
	return x;
}
int root(int n)
{
	int x=n;
	while(fa[x]!=-1)
		x=fa[x];
	return x;
}
int main()
{
	int n,m,p,a,b;
	cin>>n>>m>>p;
	for(int i=0;i<=n;i++)
		fa[i]=-1;
	for(int i=0;i<m;i++)
	{
		cin>>a>>b;
		int h1,r1=root(a,&h1);
		int h2,r2=root(b,&h2);
		if(r1!=r2)
		{
			if(h1>h2)
				fa[r2]=r1;
			else
				fa[r1]=r2;
		}
	}
	for(int i=0;i<p;i++)
	{
		cin>>a>>b;
		int r1=root(a);
		int r2=root(b);
		if(r1==r2)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
