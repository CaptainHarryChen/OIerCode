#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	double x,m=0;
	int y;
	cin>>x>>y;
	for(int i=1;i<=y;i++)
	{
		m+=x;
		x/=2;
		if(i!=y)
			m+=x;
	}
	printf("%.4lf\n%.4lf\n",m,x);
}
