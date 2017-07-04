#include<cstdio>
#include<iostream>
using namespace std;
int f[1005];
int main()
{
	int n;
	cin>>n;
	f[0]=1;
	f[1]=1;
	f[2]=2;
	for(int i=3;i<=n;i++)
	{
		for(int j=1;j<i;j++)
			f[i]+=(f[j-1]*f[i-j-1])%12345;
		f[i]+=f[i-1];
		f[i]%=12345;
	}
	cout<<f[n]<<endl;
	return 0;
}
