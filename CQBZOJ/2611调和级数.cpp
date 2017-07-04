#include<iostream>
#include<cstdio>
using namespace std;
int a[500];
int main()
{
	int n;
	double m=0;
	cin>>n;
	if(n<=0)
	{cout<<"no answer"<<endl;return 0;}
	for(int i=1;i<=n;i++)
		m+=1.0/i;
	printf("%.3lf\n",m);
	return 0;
}
