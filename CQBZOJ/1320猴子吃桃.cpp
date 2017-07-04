#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int cnt=10;
int f(int n)
{
	if(cnt==1) return n;
	else {cnt--;return f((n+1)*2);}
}
int main()
{
	int n;
	cin>>n;
	cout<<f(n)<<endl;
	return 0;
}
