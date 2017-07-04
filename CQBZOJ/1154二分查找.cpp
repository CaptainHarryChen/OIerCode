#include<cstdio>
#include<iostream>
using namespace std;
int n,s[2000000],x;
int find(int a,int b)
{
	if(a>b)
		return -2;
	int mid=(a+b)/2;
	if(x==s[mid])
		return mid;
	else if(x<s[mid])
		return find(a,mid-1);
	else
		return find(mid+1,b);
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&s[i]);
	scanf("%d",&x);
	printf("%d\n",find(0,n-1)+1);
	return 0;
}
