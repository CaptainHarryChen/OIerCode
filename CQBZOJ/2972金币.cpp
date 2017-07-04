#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	int n,i,j,sum=0;
	scanf("%d",&n);
	for(i=1,j=0;n>j;)
	{sum+=i*i;j+=i;i++;}
	for(;j>n;j--)
		sum-=(i-1);
	printf("%d",sum);
	return 0;
}
