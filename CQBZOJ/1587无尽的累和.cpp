#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
	int n,i;
	double m=0;
	cin>>n;
	for(i=1;m<n;i++)
		m+=1.0/i;
	cout<<i-1<<endl;
}
