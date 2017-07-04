#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int main()
{
	int n,a,b,c,d,s;
	cin>>n;
	a=n/1000;
	b=n/100%10;
	c=n%100/10;
	d=n%10;
	s=a+b+c+d;
	cout<<s<<endl;
}
