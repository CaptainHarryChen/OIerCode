#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	if(n>=90&&n<=100)printf("A\n");
	else if(n>=80)printf("B\n");
	else if(n>=70)printf("C\n");
	else if(n>=60)printf("D\n");
	else if(n>=0)printf("E\n");
	return 0;
}
