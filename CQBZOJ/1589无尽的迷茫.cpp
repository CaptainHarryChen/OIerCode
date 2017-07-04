#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	int a,b;
	scanf("%d%d",&a,&b);
	for(int i=max(a,b);;i++)
		if(i%a==0&&i%b==0)
		{printf("%d\n",i);return 0;}
}
