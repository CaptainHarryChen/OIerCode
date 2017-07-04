#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int main()
{
	int a,b;
	scanf("%d",&a);
	b=sqrt(a);
	if(b*b==a)
		printf("Yes\n");
	else
		printf("No\n");
	return 0;
}
