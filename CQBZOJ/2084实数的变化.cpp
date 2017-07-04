#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
using namespace std;
int main()
{
	double a;
	scanf("%lf",&a);
	if(a<0)a=-a;
	printf("%.3lf\n%.3lf\n%.3lf\n",a,sqrt(a),a*a);
	return 0;
}
