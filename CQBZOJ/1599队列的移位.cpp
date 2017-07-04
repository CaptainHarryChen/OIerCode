#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int main()
{
	int a[1000],b[1000],n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	b[n-1]=a[0];
	for(int i=1;i<n;i++)
		b[i-1]=a[i];
	for(int i=0;i<n;i++)
	{
		cout<<a[i];
		if(i!=n-1)
			cout<<' ';
	}
	cout<<endl;
	for(int i=0;i<n;i++)
	{
		cout<<b[i];
		if(i!=n-1)
			cout<<' ';
	}
	cout<<endl;
	return 0;
}
