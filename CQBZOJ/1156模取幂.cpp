#include<cstdio>
#include<iostream>
using namespace std;
int b,p,k;
int abc(int a,int b)
{
	a%=k;
	if(b==1)return a%k;
	int s=(((abc(a,b/2))%k)*((abc(a,b/2))%k))%k;
	if(b%2)
	{
		s*=a;
		s%=k;
	}
	return s;
}
int main()
{
	scanf("%d%d%d",&b,&p,&k);
	printf("%d\n",abc(b%k,p));
	return 0;
}
