#include<cstdio>
#include<iostream>
using namespace std;
int f(int m,int n)
{
	if(m<n)return 0;
	if(m==n)return 1;
	if(n==1)return 1;
	return f(m-1,n-1)+f(m-n,n);
}
int main()
{
	int n,m;
	cin>>m>>n;
	cout<<f(m+n,n)<<endl;
	return 0;
}
