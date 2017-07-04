#include<cstdio>
#include<iostream>
using namespace std;
int f[505];
int main()
{
	int n,p;
	cin>>n>>p;
	f[p]=p*2;
	for(int i=p+1;i<=n;i++)
		f[i]=f[i-1]+i;
	cout<<f[n]<<endl;
	return 0;
}
