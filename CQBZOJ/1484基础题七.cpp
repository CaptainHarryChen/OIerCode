#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int a[1010];
int main()
{
	int n,m=0;
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(j%i==0)
				a[j-1]=1-a[j-1];
	for(int i=0;i<n;i++)
		if(a[i]==1)
			m++;
	cout<<m<<endl;
	for(int i=0;i<n;i++)
		if(a[i]==1)
			cout<<i+1<<endl;
	return 0;
}
