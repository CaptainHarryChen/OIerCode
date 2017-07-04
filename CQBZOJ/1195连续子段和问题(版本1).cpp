#include<cstdio>
#include<cstring>
#include<iostream>
#define INF 2147483647
#define MAXN 500100
using namespace std;
int n,k,num[MAXN];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
	int sum=0,cnt=0;
	for(int i=1,j=0;j!=n||i!=n;)
	{
		if(sum<k)
		{
			if(j==n)break;
			j++;
			sum+=num[j];
		}
		else if(sum==k)
		{cnt++;i++;sum-=num[i-1];}
		else
		{
			if(i>j)break;
			i++;
			sum-=num[i-1];
		}
	}
	printf("%d\n",cnt);
	return 0;
}
