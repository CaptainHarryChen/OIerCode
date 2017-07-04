#include<cstdio>
#include<iostream>
using namespace std;
int m[100000];
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>m[i];
	for(int i=n-1;i>=0;i--)
	{
		cout<<m[i];
		if(i!=0)
			cout<<' ';
	}
	return 0;
}
