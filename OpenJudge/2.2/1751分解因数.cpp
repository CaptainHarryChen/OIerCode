#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int count(int x,int y)
{
	if(x==1)return 0;
	int cnt=1;
	for(int i=y;i*i<=x;i++)
		if(x%i==0)
			cnt+=count(x/i,i);
	return cnt;
}
int main()
{
	int n,x;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d",&x);
		printf("%d\n",count(x,2));
	}
	return 0;
}
