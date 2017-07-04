#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int num[20];
int main()
{
	for(int i=1;i<=10;i++)
		scanf("%d",&num[i]);
	for(int i=10;i>1;i--)
		printf("%d ",num[i]);
	printf("%d\n",num[1]);
	return 0;
}
