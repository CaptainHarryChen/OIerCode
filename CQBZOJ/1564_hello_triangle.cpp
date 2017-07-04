#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int main()
{
	int a,b,c;
	double p,s;
	cin>>a>>b>>c;
	p=(a+b+c)/2.0;
	s=sqrt(p*(p-a)*(p-b)*(p-c));
	printf("%.4lf\n",s);
}
