#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int n,s,m,h;
	cin>>n;
	s=n;
	m=n/61;
	h=m/60;
	m=m-h*60;
	s=s-m*61-h*60*61;
	printf("%02d:%02d:%02d\n",h,m,s);
}
