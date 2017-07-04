#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int f[1004];
int main()
{
	int n;
	cin>>n;
	f[0]=1;
	f[1]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j*2<=i;j++)
			f[i]+=f[j];
		f[i]++;
	}
	cout<<f[n]<<endl;
	return 0;
}
