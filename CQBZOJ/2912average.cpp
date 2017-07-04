#include<cstdio>
#include<iostream>
#include<cstring>
#define MAXN 105
using namespace std;
int n,B[MAXN],sum[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&B[i]);
	for(int i=1;i<=n;i++)
		sum[i]=B[i]*i;
	for(int i=1;i<n;i++)
		printf("%d ",sum[i]-sum[i-1]);
	printf("%d\n",sum[n]-sum[n-1]);
	return 0;
}
