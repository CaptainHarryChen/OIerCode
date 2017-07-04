#include<iostream>
#include<cstdio>
using namespace std;
int a[500];
int main()
{
    int n,m,cnt=0;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	cin>>m;
	for(int i=0;i<n;i++)
		if(a[i]<m)
			cnt++;
	cout<<cnt<<endl;
	return 0;
}
