#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	int n,a[1000]={0},m,k;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<n;i++)
	{
		m=a[0];
		for(int j=0;j<n;j++)
			if(m>=a[j])
			{
				m=a[j];
				k=j;
			}
		cout<<m;
		if(i!=n-1)
			cout<<' ';
		a[k]=9999999;
	}
	cout<<endl;
	return 0;
}
