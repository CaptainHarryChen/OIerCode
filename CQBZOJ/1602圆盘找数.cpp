#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int a[1005];
int main()
{
	int m=0,k,n;
	for(int i=0;cin>>a[i];i++)
		n=i;
	n++;
	for(int i=0;i<n-3;i++)
		if(m<a[i]+a[i+1]+a[i+2]+a[i+3])
		{
			m=a[i]+a[i+1]+a[i+2]+a[i+3];
			k=i;
		}
	if(m<a[n-3]+a[n-2]+a[n-1]+a[0])
	{
		m=a[n-3]+a[n-2]+a[n-1]+a[0];
		k=n-3;
	}
	if(m<a[n-2]+a[n-1]+a[0]+a[1])
	{
		m=a[n-2]+a[n-1]+a[n-0]+a[1];
		k=n-2;
	}
	if(m<a[n-1]+a[0]+a[1]+a[2])
	{
		m=a[n-1]+a[0]+a[1]+a[2];
		k=n-1;
	}
	cout<<k+1<<' '<<m<<endl;
	return 0;
}
