#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int main()
{
	double r,c,s;
	cin>>r;
	c=2*r*M_PI;
	s=M_PI*r*r;
	printf("%.4lf\n%.4lf\n",c,s);
}
