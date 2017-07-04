#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,num[200],p,m;
bool check(int n)
{
	for(int i=2;i*i<n;i++)
		if(n%i==0)
			return 0;
	return 1;
}
int main()
{
	scanf("%d",&n);
	m=n;
	for(int i=2;n!=1;i++)
	{
		if(!check(i))continue;
		while(n%i==0)
		{n/=i;num[p++]=i;}
	}
	printf("%d=",m);
	for(int i=0;i<p-1;i++)
		printf("%d*",num[i]);
	printf("%d\n",num[p-1]);
	return 0;
}
