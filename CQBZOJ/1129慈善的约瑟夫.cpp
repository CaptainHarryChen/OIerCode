#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n;
int x()
{
	int k=1;
	for(int i=1;k*2<=n;i++)
		k*=2;
	return 2*(n-k);
}

int main()
{
	int s=0;
	cin>>n;
	for(int i=0,key=x();n!=key+1;i++,key=x())
	{
		s+=n-key-1;
		n=key+1;
	}
	cout<<s+n*2<<endl;
	return 0;
}
