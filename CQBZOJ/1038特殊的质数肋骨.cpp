#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int N,num;
bool check(int x)
{
	for(int i=3;i*i<=x;i+=2)
		if(x%i==0)
			return 0;
	return 1;
}
void dfs(int x)
{
	if(x>N)
	{
		if(check(num))
			printf("%d\n",num);
		return;
	}
	for(int i=(x==1?2:1);i<=9;i=(i==2?3:i+2))
	{
		num*=10;num+=i;
		if(!check(num))
		{num/=10;continue;}
		dfs(x+1);
		num/=10;
	}
}
int main()
{
	scanf("%d",&N);
	dfs(1);
	return 0;
}
