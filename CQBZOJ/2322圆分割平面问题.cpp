#include<cstdio>
#include<iostream>
using namespace std;
int f[105];
int main()
{
	int n;
	cin>>n;
	f[0]=1;
	f[1]=2;
	for(int i=2;i<=n;i++)
		f[i]=f[i-1]+2*(i-1);
	cout<<f[n]<<endl;
	return 0;
}
