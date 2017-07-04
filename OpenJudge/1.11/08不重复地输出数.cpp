#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define MAXN 100100
using namespace std;
int n,num[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
	sort(num+1,num+n+1);
	int x=num[1];
	printf("%d ",x);
	for(int i=2;i<=n;i++)
		if(num[i]!=x)
		{
			x=num[i];
			printf("%d ",num[i]);
		}
	printf("\n");
	return 0;
}
