#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	double a,d;
	int b,c;
	cin>>a;
	b=(int)a;
	d=a+0.5;
	c=(int)d;
	printf("%d\n%d\n%.6lf\n",b,c,a-b);
}
