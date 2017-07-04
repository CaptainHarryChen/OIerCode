#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int main()
{
	int x;
	scanf("%d",&x);
	printf("%d\n%d\n",x-1,x+1);
	if(x<0)x=-x;
	printf("%d\n",x);
	printf("%.2lf\n",sqrt((double)x));
}
