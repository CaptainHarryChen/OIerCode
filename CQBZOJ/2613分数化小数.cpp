#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	int a,b,c;
	cin>>a>>b>>c;
	double s;
	s=((double)a)/b;
	printf("%.*lf\n",c,s);
	return 0;
}
