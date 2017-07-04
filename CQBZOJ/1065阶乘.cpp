#include<cstdio>
#include<iostream>
using namespace std;
long long N,sum=1;
int main()
{
	scanf("%d",&N);
	for(long long i=1;i<=N;i++)
	{
		sum*=i;
		while(sum%10==0)sum/=10;
		if(sum>10000000)sum%=10000000;
	}
	printf("%d\n",sum%10);
	return 0;
}
