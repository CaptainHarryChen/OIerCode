#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	int a=0,b=1,n,cnt=0;
	scanf("%d",&n);
	while(a!=b)
	{
		int s=(a+b)*(b-a+1)/2;
		if(s>n)
			a++;
		else if(s<n)
			b++;
		else
		{
			cnt++;
			a++;b++;
		}
	}
	printf("%d\n",cnt+1);
	return 0;
}
