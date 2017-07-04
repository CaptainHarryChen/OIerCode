#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define EQUATION pow(x,5)-15*pow(x,4)+85*pow(x,3)-225*x*x+274*x-121
#define A 0.0000001
double solve(double l,double r)
{
	double x=(l+r)/2;
	double s=EQUATION;
	if(s<-A)
		return solve(l,x);
	if(s>A)
		return solve(x,r);
	return x;
}
int main()
{
	printf("%.6lf\n",solve(1.5,2.4));
	return 0;
}
